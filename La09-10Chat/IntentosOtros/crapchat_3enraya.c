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

/*declaraciones de las funciones wrappers para simplificarnos la vida*/
int ReservarMemoriaComp(int n);
void* MapearMemoriaComp(int n);
int CrearSemaforos(int n, short* vals);
void BorrarSemaforos(int id);
void BloquearSemaforo(int id, int i);
void DesbloquearSemaforo(int id, int i);
union semun {
    int val;
    struct semid_ds* buf;
    unsigned short* array;
    struct seminfo* __buf;
};

enum {
    SEM_USER_1, /*el turno de la primera persona*/
    SEM_USER_2 /*el turno de la 2da persona*/
};

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

void* MapearMemoriaComp(int id) {
    void* addr;
    addr = shmat(id, NULL, 0); /*adjuntamos el segmento*/
    shmctl(id, IPC_RMID, NULL); /*y lo marcamos para que se destruya*/
    return addr;
}
int ReservarMemoriaComp(int n) {
    return shmget(IPC_PRIVATE, n, IPC_CREAT | SHM_R | SHM_W);
}

char tablero[10]; /*creamos nuestro char[] que funcionara como un tablero*/

void crearTablero(){ /* metodo para llenar con espacios el tablero para iniciar el juego*/
    int i;
    for(i =0;i<10; i++)
        tablero[i] = ' ';
}

void dibujarTablero(){ /* mostrara el char[]tablero en forma de un tablero de 3 en raya con sus respectivos datos*/
    printf("\n_%c_|_%c_|_%c_\n",tablero[1],tablero[2],tablero[3]);
    printf("_%c_|_%c_|_%c_\n",tablero[4],tablero[5],tablero[6]);
    printf(" %c | %c | %c \n",tablero[7],tablero[8],tablero[9]);
}
void verificarWin(){ /* metodo que analizara si el jugador a ganado*/
    if((tablero[1] == tablero [2] && tablero[2] == tablero[3] && tablero[1] != ' ') ||
            (tablero[1] == tablero [4] && tablero[4] == tablero[7] && tablero[4] != ' ') ||
            (tablero[2] == tablero [5] && tablero[5] == tablero[8] && tablero[2] != ' ') ||
            (tablero[3] == tablero [6] && tablero[6] == tablero[9] && tablero[3] != ' ') ||
            (tablero[4] == tablero [5] && tablero[5] == tablero[6] && tablero[4] != ' ') ||
            (tablero[7] == tablero [8] && tablero[8] == tablero[9] && tablero[7] != ' ') ||
            (tablero[1] == tablero [5] && tablero[5] == tablero[9] && tablero[1] != ' ') ||
            (tablero[3] == tablero [5] && tablero[5] == tablero[7] && tablero[3] != ' '))

        printf("Usted ha ganado");
}

int main(int argc, char* argv[]) {
    int idShMem; /*handle a la memoria compartida*/
    int idSem; /*handle al grupo de semáforos*/
    char* buf; /*dirección del buffer de memoria compartida*/
    short vals[2]; /*valores para inicializar los semáforos*/
    int miSem; /*semáforo para nuestro usuario*/
    int tuSem; /*semáforo para el otro usuario*/
    puts("Bienvenido al juego 3 en raya, presione un numero del 1 al 9 para colocar tu marca en el tablero hasta que uno gane. Escribe '\\quit' para salir\n");
    /*obtenemos el id del segmento de memoria de la línea de comandos*/
    crearTablero();
    if(argc<2) {
        /*no nos pasaron ningún id, así que lo creamos*/
        idShMem = ReservarMemoriaComp(BUFSIZ);
        buf = (char*) MapearMemoriaComp(idShMem);
        /*Queremos que los usuarios sean bloqueados cuando traten de*/
        /*hacer lock a la memoria compartida. Cuando el segundo usuario*/
        /*inicia el programa, desbloquearoan al primero para que pueda tipear.*/
        /*Para eso son los ceros.*/
        vals[SEM_USER_1]=0;
        vals[SEM_USER_2]=0;
        idSem=CrearSemaforos(2,vals);
        /*guardamos el id del semáforo en la memoria compartida para que*/
        /*el otro usuario pueda obtenerlo*/
        *((int*) buf) =idSem;
        miSem = SEM_USER_1;
        tuSem = SEM_USER_2;
        /*escribimos el id del segmento de memoria compartida para que el otro*/
        /*usuario sepa y pueda chatear con nosotros.*/
        printf("Eres el jugador uno. El id de la memoria compartida es: %d\n", idShMem); 
        printf("Esperando al jugador dos...\n");
    }
    else {
        /*tenemos un valor! quiere decir que somos el usuario dos.*/
        idShMem = atoi(argv[1]);
        buf = (char*) MapearMemoriaComp(idShMem);
        /*obtenemos el id del grupo de semaforos desde la memoria compartida*/
        idSem = *((int*) buf);
        /*grabamos a qué semáforos tenemos que esperar*/
        /*recordemos que aquí los roles cambian*/
        miSem=SEM_USER_2;
        tuSem=SEM_USER_1;
        /*Ponemos una cadena vacía en la memoria compartida.*/
        sprintf(buf, "");
        /*desbloqueamos al otro usuario para indicar que pueden hablar*/
        puts("Eres el jugador dos. Avisando al jugador uno...");
        DesbloquearSemaforo(idSem, tuSem);
    }
    for(;;) {
        verificarWin(); 
        dibujarTablero();
        /*Esperar hasta que sea mi turno de hablar*/
        BloquearSemaforo(idSem, miSem);
        /*salió el otro usuario?*/
        if(strcmp(buf, "\\quit\n")==0)
            break;
        int x = atoi(buf);
        tablero[x] = '0';
        /*imprimir la respuesta, si hay alguna*/
        if(strlen(buf)>0){
            dibujarTablero();
        }
        /*obtener tu respuesta*/
        printf("> ");
        fgets(buf, BUFSIZ, stdin);
        int y = atoi(buf);
        tablero[y] = 'x';

        /*Pasamos el control al otro usuario.*/
        DesbloquearSemaforo(idSem, tuSem);

        /*quieres salir?*/
        if(strcmp(buf, "\\quit\n") == 0)
            break;
    }
    /*el primer usuario tiene que liberar los semáforos.*/
    if(miSem == SEM_USER_1)
        BorrarSemaforos(idSem);
}
