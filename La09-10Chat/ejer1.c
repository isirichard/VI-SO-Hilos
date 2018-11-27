/*semaforo_1.c*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>
/* estructure union smun para semop*/
int CrearSemaforos(int n, short* vals);
void BorrarSemaforos(int id);
void BloquearSemaforo(int id, int i);
void DesbloquearSemaforo(int id, int i);

int CrearSemaforos(int n, short* vals) {
	union semun arg;
	int id;
	id=semget(IPC_PRIVATE, n, SHM_R | SHM_W);
	arg.array=vals;
	semctl(id, 0, SETALL, arg);
	return id;
}
void BorrarSemaforos(int id) {
	if(semctl(id, 0, IPC_RMID, NULL)==-1) {
		perror("Error liberando semáforo!");
		exit(EXIT_FAILURE);
	}
}
void BloquearSemaforo(int id, int i) {
	struct sembuf sb;
	sb.sem_num = i;
	sb.sem_op=-1;
	sb.sem_flg=SEM_UNDO;
	semop(id,&sb,1);
}
void DesbloquearSemaforo(int id, int i) {
	struct sembuf sb;
	sb.sem_num = i;
	sb.sem_op = 1;
	sb.sem_flg = SEM_UNDO;
	semop(id, &sb, 1);
}
union semun {
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *_buf;
};
main() {
	key_t clave; /*clave de semaforo*/
	int idSemaforo; /*conjunto de semaforo*/
	idSemaforo = CrearSemaforos(3,vals);
	
	struct sembuf operacion; /* sembuf operacion rojo y verde */
	union semun arg; /* union semun arg */
	int i=0; 
	clave = ftok("/bin/ls",33); /*obteniendo clave*/
	if (clave == (key_t)-1) {	/* try catch obteniendo clave*/
		printf("No puedo conseguir la clave de semaforo\n");
		exit(0);
	}
	idSemaforo=semget(clave,10,0600|IPC_CREAT); /*obteniendo conjunt de semaforos*/
	if (idSemaforo == -1) {		/* try catch conjunto de semaforos*/
		printf("No puedo crear el semaforo\n");
		exit(0);
	}
	arg.val = 0; /*empezando en rojo */
	semctl(idSemaforo,0,SETVAL,&arg); /*iniciando el semaforo*/
	operacion.sem_num = 0;
	operacion.sem_op = -1; /*la operación es decrementar*/
	operacion.sem_flg = 0;
	while(1) {
		printf("Esperando semaforo %d\n",i);
		semop(idSemaforo,&operacion,1);
		printf("Salgo del semaforo %d\n",i);
		i++;
	}
}