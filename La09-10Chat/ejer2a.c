/*semaforo_2.c*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
/*usando estructura para crear 3 constantes para los 3 semaforos con valor 0 1 2 respectivamente*/
enum {
    SEM_USER_1, /* para el semaforo 0*/
    SEM_USER_2, /* para el semaforo 1*/
    SEM_USER_3 /* para el semaforo 2*/
};

/*crando estructura para memoria compartida iniciación de los semaforos*/
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
    struct seminfo *_buf;
};

/*método wrapper para crear semaforos*/
int CrearSemaforos(int n, short* vals) {
    key_t clave = ftok("/bin/ls",33);
    union semun arg;
    int id;
    id=semget(clave,3,0600|IPC_CREAT);
    arg.array=vals;
    semctl(id, 0, SETALL, arg);
    return id;
}
/*método wrapper para borrar semaforos*/
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

main() {
    
    key_t clave;
    int idSemaforo;
    struct sembuf operacion;
    union semun arg;
    int i=0;
    /*inicializando vals en las respectiva ubicación con cero*/
    short vals[3];
    vals[SEM_USER_1] = 0;
    vals[SEM_USER_2] = 0;
    vals[SEM_USER_3] = 0;
    /*mandando a vals para que los tres semaforos inicien en 0*/
    idSemaforo = CrearSemaforos(3,vals);

    int x;
    /*realizando 20 llamadas de asistencia del agente para fumar*/
    for(i=0; i<20; i++) {

        x = rand()%3;
        /*atentiendo de manera random al semaforo correspondiente gracias a la operación*/
        /*struct sembuf operación y sus atributos.*/
        if(x == 0){
            
            DesbloquearSemaforo(idSemaforo,x);
            
            /*
            operacion.sem_num = 0;
            operacion.sem_op = 1;
            operacion.sem_flg = 0;
            */
            printf("Coloco en la mesa papel y cerillos\n");
            semop(idSemaforo,&operacion,1);
            sleep(2);
        }
        if(x == 1){
             
            DesbloquearSemaforo(idSemaforo,x);
            
            /*
            operacion.sem_num = 1;
            operacion.sem_op = 1;
            operacion.sem_flg = 0;
            */
            printf("Coloco en la mesa tabaco y cerillos\n");
            semop(idSemaforo,&operacion,1);
            sleep(2);
        }
        if(x == 2){
             
            DesbloquearSemaforo(idSemaforo,x);
            
            /*
            operacion.sem_num = 2;
            operacion.sem_op = 1;
            operacion.sem_flg = 0;
            */
            printf("Coloco en la mesa papel y tacabo\n");
            semop(idSemaforo,&operacion,1);
            sleep(2);
        }

    }
    /*borrando semaforos al terminar*/
    /*BorrarSemaforos(idSemaforo);*/

}
