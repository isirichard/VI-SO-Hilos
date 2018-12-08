/*semaforo_2.c*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
    struct seminfo *_buf;
};
main() {
    key_t clave;
    int idSemaforo;
    struct sembuf operacion;
    union semun arg;
    int i=0;
    clave = ftok("/bin/ls",33);
    if (clave == (key_t)-1) {
        printf("No puedo conseguir la clave de semaforo\n");
        exit(0);
    }
    idSemaforo=semget(clave,10,0600|IPC_CREAT);
    if (idSemaforo == -1) {
        printf("No puedo crear el semaforo\n");
        exit(0);
    }
    int x;
    for(i=0; i<20; i++) {

        x = rand()%3;
        if(x == 0){
            operacion.sem_num = 0;
            operacion.sem_op = 1;
            operacion.sem_flg = 0;
            printf("Coloco en la mesa papel y cerillos\n");
            semop(idSemaforo,&operacion,1);
            sleep(2);
        }
        if(x == 1){
            operacion.sem_num = 1;
            operacion.sem_op = 1;
            operacion.sem_flg = 0;
            printf("Coloco en la mesa tabaco y cerillos\n");
            semop(idSemaforo,&operacion,1);
            sleep(2);
        }
        if(x == 2){
            operacion.sem_num = 2;
            operacion.sem_op = 1;
            operacion.sem_flg = 0;
            printf("Coloco en la mesa papel y tacabo\n");
            semop(idSemaforo,&operacion,1);
            sleep(2);
        }

    }
}
