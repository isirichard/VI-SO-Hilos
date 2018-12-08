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

//declaraciones de las funciones wrappers para simplificarnos la vida
int ReservarMemoriaComp(int n);
void* MapearMemoriaComp(int id);
int CrearSemaforos(int n, short* vals);
void BorrarSemaforos(int id);
void BloquearSemaforo(int id, int i);
void DesbloquearSemaforo(int id, int i);
int hayGanador();
int noHayGanador();

void imprimirEstado();

char casillas[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};


 union semun {
           int              val;    /* Value for SETVAL */
           struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
           unsigned short  *array;  /* Array for GETALL, SETALL */
           struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                       (Linux specific) */
     };


enum {
      SEM_USER_1,//el turno de la primera persona
      SEM_USER_2 //el turno de la 2da persona
     };

int main(int argc, char* argv[])
{
  int idShMem;
  //handle a la memoria compartida
  int idSem;
  //handle al grupo de semáforos
  char* buf;
  //dirección del buffer de memoria compartida
  short vals[2];
  int miSem;
  int tuSem;
  //valores para inicializar los semáforos
  //semáforo para nuestro usuario
  //semáforo para el otro usuario
  puts("Bienvenido a CrapChat! Escribe '\\quit' para salir\n");
  //obtenemos el id del segmento de memoria de la línea de comandos
  if(argc<2)
  {
    //no nos pasaron ningún id, así que lo creamos
    idShMem = ReservarMemoriaComp(BUFSIZ);
    buf = (char*) MapearMemoriaComp(idShMem);
    //Queremos que los usuarios sean bloqueados cuando traten de
    //hacer lock a la memoria compartida. Cuando el segundo usuario
    //inicia el programa, desbloquearoan al primero para que pueda tipear.
    //Para eso son los ceros.
    vals[SEM_USER_1]=0;
    vals[SEM_USER_2]=0;
    idSem=CrearSemaforos(2,vals);
    //guardamos el id del semáforo en la memoria compartida para que
    //el otro usuario pueda obtenerlo
    *((int*) buf) =idSem;
    miSem = SEM_USER_1;
    tuSem = SEM_USER_2;
    //escribimos el id del segmento de memoria compartida para que el otro
    //usuario sepa y pueda chatear con nosotros.
    printf("Eres el usuario uno. El id de la memoria compartida es: %d\n",
    idShMem);
    printf("Esperando al usuario dos...\n");
  }
  else
  {
    //tenemos un valor! quiere decir que somos el usuario dos.
    idShMem = atoi(argv[1]);
    buf = (char*) MapearMemoriaComp(idShMem);
    //obtenemos el id del grupo de semaforos desde la memoria compartida
    idSem = *((int*) buf);
    //grabamos a qué semáforos tenemos que esperar
    //recordemos que aquí los roles cambian
    miSem=SEM_USER_2;
    tuSem=SEM_USER_1;
    //Ponemos una cadena vacía en la memoria compartida.
    sprintf(buf, "");
    //desbloqueamos al otro usuario para indicar que pueden hablar
    puts("Eres el usuario dos. Avisando al usuario uno...");
    DesbloquearSemaforo(idSem, tuSem);
  }
  
  imprimirEstado(); // imprimir tablero inicial
  
  for(;;)
  {
    //Esperar hasta que sea mi turno de hablar
    BloquearSemaforo(idSem, miSem);
    //salió el otro usuario?
    if(strcmp(buf, "\\quit\n")==0)
      break;
    //imprimir la respuesta, si hay alguna
    if(strlen(buf)>0) {
      printf("Respuesta:\n");
      
      int pos;
      char marca;

      pos = buf[0] - '0';  // convierte un caracter numerico a su valor int (ejemplo el char '9' lo convierte a 9 decimal)    
 
      
      // saber si esta jugando el jugador 1 o 2 para poner la marca correcta
      if (miSem == SEM_USER_2) marca = 'X';
      else marca = 'O';
      
      casillas[pos-1] = marca; // se resta 1 porque las casillas empiesan de 0 y terminan en 8 en el arreglo
      
      imprimirEstado();
      
      if (hayGanador()) {
        printf("Perdiste, Tu Oponente Ganó\n");
        break;
      }
    }
    
    
    
    //obtener tu respuesta
    int mov_correcto = 0;
    while (!mov_correcto) { // iterar hasta obtener un movimiento valido
      printf("> ");
      fgets(buf, BUFSIZ, stdin);
    
      int pos;
      char marca;

      pos = buf[0] - '0';  // convierte un caracter numerico a su valor int (ejemplo el char '9' lo convierte a 9 decimal)    
      
      // saber si esta jugando el jugador 1 o 2 para poner la marca correcta
      if (miSem == SEM_USER_1)   marca = 'X';
      else  marca = 'O';
 
      if (casillas[pos-1] == buf[0]){  // permitir llenar solo casillas que aun no han sido asignadas
        casillas[pos-1] = marca; // se resta 1 porque las casillas empiesan de 0 y terminan en 8 en el arreglo
        mov_correcto = 1;
      }
      else {
        printf("casilla ocupada\n");
      }
    }
    imprimirEstado();
     if (hayGanador()) {
        printf("!! Ganaste el Juego ¡¡\n");
        break; // juego terminado
      }
    //Pasamos el control al otro usuario.
    DesbloquearSemaforo(idSem, tuSem);
    //quieres salir?
    if(strcmp(buf, "\\quit\n") == 0)
      break;
  }
  //el primer usuario tiene que liberar los semáforos.
  if(miSem == SEM_USER_1)
    BorrarSemaforos(idSem);
}

void imprimirEstado() {
    
    printf("------\n");
    printf ("%c|%c|%c\n", casillas[0], casillas[1], casillas[2]);
    printf ("-----\n");
    printf ("%c|%c|%c\n", casillas[3], casillas[4], casillas[5]);
    printf ("-----\n");
    printf ("%c|%c|%c\n", casillas[6], casillas[7], casillas[8]);
    printf("------\n\n");

}

int hayGanador() {
  
  // verificar columnas completas
  for (int i = 0; i < 3; ++i) {
    if (casillas[i] == casillas[i+3]) { // doble if porque en c no es posible comparar 3 valores al mismo tiempo
      if (casillas[i] == casillas[i+6])
        return 1;
    } 
  }
  
  
  
  // verificar filas completas
  for (int j = 0; j < 7; j=j+3) {
    if (casillas[j] == casillas[j+1]) { // doble if porque en c no es posible comparar 3 valores al mismo tiempo
      if (casillas[j] == casillas[j+2])
        return 1;
    }
  }
  
  
  
  // verificar diagonales completas
  if (casillas[0] == casillas[4]) {
    if (casillas[0] == casillas[8])
      return 1;
  
  }
  if (casillas[2] == casillas[4]) {
    if (casillas[2] == casillas[6])
      return 1;
  }
  // no hubo nada completo
  return 0;
}

  int noHayGanador(){
    int i,cont=0;
    for(i=0;i<9;i++){
      if(casillas[i]=='X'||casillas[i]=='O')
        cont++;    
    }
    if (cont==9){
      return 1;
    }  
  }





int ReservarMemoriaComp(int n)
{
  assert(n > 0); /* Idiot-proof the call. */

  return shmget(IPC_PRIVATE, n, IPC_CREAT | SHM_R | SHM_W);
}

void* MapearMemoriaComp(int id)
{
  void* addr;

  assert(id != 0); /* Idiot-proof the call. */

  addr = shmat(id, NULL, 0); /* Attach the segment... */ 
  shmctl(id, IPC_RMID, NULL); /* ...and mark it destroyed. */ 
  return addr;
}

int CrearSemaforos(int n, short* vals)
{
  union semun arg; 
  int id;

  assert(n > 0); /* You need at least one! */ 
  assert(vals != NULL); /* And they need initialising! */

  id = semget(IPC_PRIVATE, n, SHM_R | SHM_W);

  arg.array = vals;
  semctl(id, 0, SETALL, arg);

  return id;
}

void BorrarSemaforos(int id)
{
  if (semctl(id, 0, IPC_RMID, NULL) == -1)
  {
    perror("Error releasing semaphore!"); 
    exit(EXIT_FAILURE);
  }
}

void BloquearSemaforo(int id, int i)
{
  struct sembuf sb;
  sb.sem_num = i;

  sb.sem_op = -1; 
  sb.sem_flg = SEM_UNDO; 
  semop(id, &sb, 1);
}

void DesbloquearSemaforo(int id, int i)
{
  struct sembuf sb;
  sb.sem_num = i; 
  sb.sem_op = 1; 
  sb.sem_flg = SEM_UNDO; 
  semop(id, &sb, 1);
}
