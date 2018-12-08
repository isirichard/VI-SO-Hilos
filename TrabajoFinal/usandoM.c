/*
* crapchat_v2.c
* CrapChat original hecho por Keith Gaughan <kmgaughan@eircom.net>
* Adaptación y traducción al español por Gustavo Puma
*
* Software libre bajo la licencia DSL:
* http://www.dsl.org/copyleft/dsl.txt
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
/*
declaraciones de las funciones wrappers para simplificarnos la vida
*/
int ReservarMemoriaComp(int n);
void* MapearMemoriaComp(int n);
int CrearSemaforos(int n, short* vals);
void BorrarSemaforos(int id);
void BloquearSemaforo(int id, int i);
void DesbloquearSemaforo(int id, int i);
/* enum para cambiar usuario */
typedef struct{
	char buf[50];
	int sema;
	enum {
		usandoH,
		usandoM,
		usandoVacio
	}cartel;
	enum {
		colaH,
		colaM,
		colaVacio
	}cola;
} variable;

enum {
	SEM_USER_1, /*el turno de la primera persona*/
	SEM_USER_2 /*el turno de la 2da persona*/
};
/* union para inicializarlo */
union semun {
	int val;
	struct semid_ds* buf;
	unsigned short* array;
	struct seminfo* __buf;
};

/*
**Reserva un segmento de memoria compartida
**
**n es el tamaño (en bytes) del pedazo a reservar
**retorna el id del pedazo de memoria compartida.
*/
int ReservarMemoriaComp(int n) {
	return shmget(IPC_PRIVATE, n*sizeof(variable), IPC_CREAT | SHM_R | SHM_W);
}
/*
**Mapea un segmento de memoria compartida a nuestro
**espacio de memoria
**
**id bloque de memoria compartida a mapear
**retorna la direccion del bloque mapeado
*/
void* MapearMemoriaComp(int id) {
	void* addr;
	addr = shmat(id, NULL, 0); /*adjuntamos el segmento*/
	shmctl(id, IPC_RMID, NULL); /*y lo marcamos para que se destruya*/
	return addr;
}

/*
**Crea un nuevo grupo de semáforos
**
**n, el número de semáforos
**vals, los valores por defecto para inicializar
**retorna el id del grupo de semáforos
*/
int CrearSemaforos(int n, short* vals) {
	union semun arg;
	int id;
	id=semget(IPC_PRIVATE, n, SHM_R | SHM_W);
	arg.array=vals;
	semctl(id, 0, SETALL, arg);
	return id;
}
/*
**Libera el grupo de semáforos indicado
**
**id, el id del grupo de semáforos
*/
void BorrarSemaforos(int id) {
	if(semctl(id, 0, IPC_RMID, NULL)==-1) {
		perror("Error liberando semáforo!");
		exit(EXIT_FAILURE);
	}
}
/*
**Bloquea a un semáforo dentro de un grupo
**
**id, id del grupo de semáforos al que pertenece
**i, semáforo a bloquear
**si ya está bloqueado, duermes
*/
void BloquearSemaforo(int id, int i) {
	struct sembuf sb;
	sb.sem_num = i;
	sb.sem_op=-1;
	sb.sem_flg=SEM_UNDO;
	semop(id,&sb,1);
}
/*
**Desbloquea a un semáforo dentro de un grupo
**
**id, id del grupo de semáforos al que pertenece
**i, semáforo a desbloquear
*/
void DesbloquearSemaforo(int id, int i) {
	struct sembuf sb;
	sb.sem_num = i;
	sb.sem_op = 1;
	sb.sem_flg = SEM_UNDO;
	semop(id, &sb, 1);
}


int main(int argc, char* argv[]) {
variable *var;
int idShMem; /*handle a la memoria compartida*/
int idSem; /*handle al grupo de semáforos*/
/*char* buf; /*dirección del buffer de memoria compartida*/
short vals[2]; /*valores para inicializar los semáforos*/
int miSem; /*semáforo para nuestro usuario*/
int tuSem; /*semáforo para el otro usuario*/
	puts("Bienvenido a CrapChat! Escribe '\\quit' para salir\n");
/*obtenemos el id del segmento de memoria de la línea de comandos*/
	if(argc<2) {

/*no nos pasaron ningún id, así que lo creamos*/
		/*idShMem = ReservarMemoriaComp(BUFSIZ);*/
		idShMem = ReservarMemoriaComp(1);
		/*buf = (char*) MapearMemoriaComp(idShMem);*/
		var = (variable*) MapearMemoriaComp(idShMem);
/*Queremos que los usuarios sean bloqueados cuando traten de*/
/*hacer lock a la memoria compartida. Cuan|do el segundo usuario*/
/*inicia el programa, desbloquearoan al primero para que pueda tipear.*/
/*Para eso son los ceros.*/
		vals[SEM_USER_1]=0;
		vals[SEM_USER_2]=0;
		/*CREAR E INICIALIZAR EL SEMAFORO*/
		idSem=CrearSemaforos(2,vals);

/*guardamos el id del semáforo en la memoria compartida para que*/
/*el otro usuario pueda obtenerlo*/
		
		var->sema = idSem;
		printf("El var->buf es: %s\n",var->buf );
		printf("El id es: %d\n",var->sema );
		/* *((int*) buf) =idSem;*/
		miSem = SEM_USER_1;
		tuSem = SEM_USER_2;
/*escribimos el id del segmento de memoria compartida para que el otro*/
/*usuario sepa y pueda chatear con nosotros.*/
		printf("Eres el usuario uno. El id de la memoria compartida es: %d\n",idShMem);
		printf("Esperando al usuario dos...\n");
	}
	else {
/*tenemos un valor! quiere decir que somos el usuario dos.*/
		idShMem = atoi(argv[1]);
		/*buf = (char*) MapearMemoriaComp(idShMem);*/
		var = (variable *) MapearMemoriaComp(idShMem);
/*obtenemos el id del grupo de semaforos desde la memoria compartida*/
		/*idSem = *((int*) buf);*/
		idSem = var->sema;
		printf("El id recibido de var-sema es: %d\n",var->sema );
		printf("El id recibido es: %d\n",idSem );
/*grabamos a qué semáforos tenemos que esperar*/
/*recordemos que aquí los roles cambian*/
		miSem=SEM_USER_2;
		tuSem=SEM_USER_1;
/*Ponemos una cadena vacía en la memoria compartida.*/
		/*sprintf(buf, "");*/
		strcpy(var->buf , "");
		printf("El var->buf es: %s\n",var->buf );
/*desbloqueamos al otro usuario para indicar que pueden hablar*/
		puts("Eres el usuario dos. Avisando al usuario uno...");
		DesbloquearSemaforo(idSem, tuSem);
	}
	for(;;) {
/*Esperar hasta que sea mi turno de hablar*/
		BloquearSemaforo(idSem, miSem);
/*salió el otro usuario?*/
		/*if(strcmp(buf, "\\quit\n")==0)*/
		/*buf=var->buf;*/
		printf("El id general es: %d\n",idSem );
		/*printf("El buf es: %s\n",buf);*/
		printf("El var->buf es: %s\n",var->buf );
		if(strcmp(var->buf, "\\quit\n")==0)
			break;
/*imprimir la respuesta, si hay alguna*/
		if(strlen(var->buf)>0)
			printf("Respuesta: %s", var->buf);
/*obtener tu respuesta*/
		printf("> ");
		fgets(var->buf, BUFSIZ, stdin);
/*Pasamos el control al otro usuario.*/
		DesbloquearSemaforo(idSem, tuSem);
/*quieres salir?*/
		if(strcmp(var->buf, "\\quit\n") == 0)
			break;
	}
/*el primer usuario tiene que liberar los semáforos.*/
	if(miSem == SEM_USER_1)
		BorrarSemaforos(idSem);
}


