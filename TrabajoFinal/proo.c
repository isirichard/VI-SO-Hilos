
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

int ReservarMemoriaComp(int n);
void* MapearMemoriaComp(int n);
int CrearSemaforos(int n, short* vals);
void BorrarSemaforos(int id);
void BloquearSemaforo(int id, int i);
void DesbloquearSemaforo(int id, int i);
void entraMujer();
void saleMujer();
void entraHombre();
void saleHombre();

int lim = 0;
int cartel = 0;
// 0 = vacio
// 1 = mujer
// 2 = hombrei
char colaSH[] = {"MMMHMMHM"};


typedef struct{
    char buf[50];
    int sema;
    int limite;
    int usando;
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
    SEM_USERP_1, 
    SEM_USERH_2,
    SEM_USERM_3 
};

union semun {
    int val;
    struct semid_ds* buf;
    unsigned short* array;
    struct seminfo* __buf;
};

void entraMujer(){
    if(cartel != 2){
        if(lim == 2){
            printf("El SSHH al limite, esperando que se desocupe el baño");
        } else{
            cartel = 1;
            printf("Entrando Mujer al SSHH...\n");
            lim++;
        }
    }
    else{
        printf("SSHH ocupado por Hombres, espere a que salgan\n");
    }
    sleep(1);
}
void saleMujer(){
    printf("Saliendo Mujer del SSHH...\n");
    lim--;
    if(lim == 0)
        cartel = 0;    

}

void entraHombre(){
    if(cartel != 1){
        if(lim == 2){
            printf("El SSHH al limite, esperando que se desocupe el baño");
        } else{
            cartel = 1;
            printf("Entrando Hombre al SSHH...\n");
            lim++;
        }   
    }
    else{
        printf("SSHH ocupado por Mujeres, espere a que salgan\n");
    }
    sleep(1);
}
void saleHombre(){
    printf("Saliendo Hombre del SSHH...\n");
    lim--;
    if(lim == 0)
        cartel = 0;

}

int ReservarMemoriaComp(int n) {
    return shmget(IPC_PRIVATE, n*sizeof(variable), IPC_CREAT | SHM_R | SHM_W);
}

void* MapearMemoriaComp(int id) {
    void* addr;
    addr = shmat(id, NULL, 0);
    shmctl(id, IPC_RMID, NULL); 
    return addr;
}

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

int main(int argc, char* argv[]) {
    variable *var;
    int idShMem; 
    int idSem; 
    short vals[3]; 
    int miSem; 
    int tuSem;
    int suSem;


    if(argc<2) {
        puts("Bienvenido a Proyecto Final!");
        idShMem = ReservarMemoriaComp(1);
        var = (variable*) MapearMemoriaComp(idShMem);
        vals[SEM_USERP_1]=0;
        vals[SEM_USERH_2]=0;
        vals[SEM_USERM_3]=0;

        idSem=CrearSemaforos(3,vals);
        var->sema = idSem;
        var->limite = 2;
        var->cartel = usandoVacio;
        var->usando = 0;

        miSem = SEM_USERP_1;
        tuSem = SEM_USERH_2;
        suSem = SEM_USERM_3;

        printf("Proceso Principal respeta el orden de la cola. El id de la memoria compartida es: %d\n",idShMem);
        int i;
        for (i = 0; i < sizeof(colaSH); i++)
            printf("%c ", colaSH[i]);
        printf("=> ");
        printf("\n");
        fflush(stdout);
        printf("Limite del SSHH : %i\n",var->limite );
        if(var->cartel == 2)
            printf("Estado del cartel : vacio\n");


        printf("Esperando en cola al proceso H de control de Hombres...\n");
        BloquearSemaforo(idSem, miSem);
        printf("Esperando en cola al proceso M de control de Mujeres...\n");
        BloquearSemaforo(idSem, miSem);
        printf("Semaforos sincronizados...\n\n");

        for(i = sizeof(colaSH); i >=0 ; i--) {
            if(colaSH[i]=='H'){
                DesbloquearSemaforo(idSem,tuSem);
                entraHombre();
                saleHombre();

            }
            if(colaSH[i]=='M'){
                DesbloquearSemaforo(idSem,suSem);
                entraMujer();
                saleMujer();

            }
        }
        printf("Cola vacia... Fin del proceso...\n");
    }
    else {
        if(strcmp("H", argv[2])==0){
            idShMem = atoi(argv[1]);
            var = (variable *) MapearMemoriaComp(idShMem);
            idSem = var->sema;

            miSem = SEM_USERH_2;
            tuSem = SEM_USERP_1;

            puts("Eres el proceso H. Avisando al proceso Principal...");

            DesbloquearSemaforo(idSem, tuSem);
            for (;;){
                BloquearSemaforo(idSem, miSem);
                entraHombre();
                saleHombre();
                DesbloquearSemaforo(idSem,tuSem);

            }
        }
        if(strcmp("M", argv[2])==0){
            idShMem = atoi(argv[1]);
            var = (variable *) MapearMemoriaComp(idShMem);
            idSem = var->sema;

            miSem = SEM_USERM_3;
            tuSem = SEM_USERP_1;

            puts("Eres el proceso M. Avisando al proceso Principal...");

            DesbloquearSemaforo(idSem, tuSem);
            for (;;){
                BloquearSemaforo(idSem, miSem);
                entraMujer();
                saleMujer();
                DesbloquearSemaforo(idSem,tuSem);

            }
        }
    }



    /*
       if(miSem == SEM_USERP_1)
       BorrarSemaforos(idSem);
     */
}



