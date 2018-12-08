/*semaforo_2.c*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
enum {
    SEM_USER_1, /* para el semaforo 0*/
    SEM_USER_2, /* para el semaforo 1*/
    SEM_USER_3 /* para el semaforo 2*/
};
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
    struct seminfo *_buf;
};
int CrearSemaforos(int n, short* vals) {
    key_t clave = ftok("/bin/ls",33);
    union semun arg;
    int id;
    id=semget(clave,3,0600|IPC_CREAT);
    return id;
}
main() {
    key_t clave;
    int idSemaforo;
    struct sembuf operacion;
    union semun arg;
    int i=0;
    short vals[3];
    vals[SEM_USER_1] = 0;
    vals[SEM_USER_2] = 0;
    vals[SEM_USER_3] = 0;
  
    idSemaforo = CrearSemaforos(3,vals);
    operacion.sem_num = 1;
    operacion.sem_op = -1;
    operacion.sem_flg = 0;
    while(1) {
        printf("Tengo papel, esperando que el agente coloque tabaco y cerillo\n");
        semop(idSemaforo,&operacion,1);
        printf("fumando\n");

    }
}
