/*
* crapchat_v2.c editado para tres en raya
  Gerald Zea
  Iam Contreras
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

int ReservarMemoriaComp(int n);
void *MapearMemoriaComp(int n);
int CrearSemaforos(int n, short *vals);
void BorrarSemaforos(int id);
void BloquearSemaforo(int id, int i);
void DesbloquearSemaforo(int id, int i);
enum
{
  SEM_USER_1,
  SEM_USER_2
};
union semun {
  int val;
  struct semid_ds *buf;
  unsigned short *array;
  struct seminfo *__buf;
};
int main(int argc, char *argv[])
{
  int idShMem;
  int idSem;
  char *buf;
  short vals[2];
  int miSem;
  int tuSem;
  // variables de ayuda indicando si empato o gano
  int jugador = 1, empate = 0, ganar = 0;
  //posiciones del tablero para poner el numero donde ira la letra, se empieza con X
  char c1 = '1', c2 = '2', c3 = '3', c4 = '4', c5 = '5', c6 = '6', c7 = '7', c8 = '8', c9 = '9', letra = 'X';
  puts("Bienvenido a CrapChat para tres en raya! Escribe '\\quit' para salir\n");

  if (argc < 2)
  {
    idShMem = ReservarMemoriaComp(BUFSIZ);
    buf = (char *)MapearMemoriaComp(idShMem);
    vals[SEM_USER_1] = 0;
    vals[SEM_USER_2] = 0;
    idSem = CrearSemaforos(2, vals);
    *((int *)buf) = idSem;
    miSem = SEM_USER_1;
    tuSem = SEM_USER_2;
    printf("Eres el usuario uno. El id de la memoria compartida es: %d\n", idShMem);
    printf("Esperando al usuario dos...\n");
  }
  else
  {
    idShMem = atoi(argv[1]);
    buf = (char *)MapearMemoriaComp(idShMem);
    idSem = *((int *)buf);
    miSem = SEM_USER_2;
    tuSem = SEM_USER_1;
    sprintf(buf, "");
    puts("Eres el usuario dos. Avisando al usuario uno...");
    DesbloquearSemaforo(idSem, tuSem);
  }
  //Se muestra el tablero para ambos jugadores antes de empezar a jugar
  printf("JUEGO DEL TRES EN RAYA, Para volver empezar presione y , para terminar presione n\n");
  printf("\n letra: %c\n", letra);
  printf("\n %c | %c | %c\n", c1, c2, c3);
  printf("---+---+---\n");
  printf("\n %c | %c | %c\n", c4, c5, c6);
  printf("---+---+---\n");
  printf("\n %c | %c | %c\n\n", c7, c8, c9);

  for (;;)
  {
    //Bloqueo semaforo
    BloquearSemaforo(idSem, miSem);
    //Si sale el otro usuario con el comando \quit
    if (strcmp(buf, "\\quit\n") == 0)
      break;
    //Respuesta, del jugador anterior
    if (strlen(buf) > 0)
    {
      printf("Respuesta: %s", buf);
      // si la respuesta fue y o Y se jugara de nuevo, se resetea todo y termina el turno
      if (*buf == 'y' || *buf == 'Y')
      {
        jugador = 1, empate = 0, ganar = 0;
        c1 = '1', c2 = '2', c3 = '3', c4 = '4', c5 = '5', c6 = '6', c7 = '7', c8 = '8', c9 = '9', letra = 'X';
        printf("\n letra: %c\n", letra);
        printf("\n %c | %c | %c\n", c1, c2, c3);
        printf("---+---+---\n");
        printf("\n %c | %c | %c\n", c4, c5, c6);
        printf("---+---+---\n");
        printf("\n %c | %c | %c\n\n", c7, c8, c9);
      }
      else
      {
        //Si la respuesta fue no del otro jugador, se termina el jugador actual
        if (*buf == 'n' || *buf == 'N')
        {
          exit(0);
        }
        //Si no fue n/y entonce comienzan a guardarse las posiciones del jugador anterior en base al buf que envio
        if (*buf == '1')
        {
          c1 = letra;
        }
        else if (*buf == '2')
        {

          c2 = letra;
        }
        else if (*buf == '3')
        {
          c3 = letra;
        }
        else if (*buf == '4')
        {
          c4 = letra;
        }
        else if (*buf == '5')
        {
          c5 = letra;
        }
        else if (*buf == '6')
        {
          c6 = letra;
        }
        else if (*buf == '7')
        {
          c7 = letra;
        }
        else if (*buf == '8')
        {
          c8 = letra;
        }
        else if (*buf == '9')
        {
          c9 = letra;
        }
        //Como es el siguiente jugador le sacamos modulo indicando par jugador 1, impar jugador 2, se cambian las letras
        jugador++;
        if (jugador % 2 == 0)
        {
          letra = 'O';
        }
        else
        {
          letra = 'X';
        }
        //Se imprime el tablero para ver como quedo del jugador anterior
        printf("\n letra: %c\n", letra);
        printf("\n %c | %c | %c\n", c1, c2, c3);
        printf("---+---+---\n");
        printf("\n %c | %c | %c\n", c4, c5, c6);
        printf("---+---+---\n");
        printf("\n %c | %c | %c\n\n", c7, c8, c9);

        //Se analiza si gano el jugador anterior
        if (c1 == 'X' || c1 == 'O')
        {
          if (c2 == c1 && c3 == c1)
          {
            ganar = 1;
          }

          if (c4 == c1 && c7 == c1)
          {
            ganar = 1;
          }
        }
        if (c5 == 'X' || c5 == 'O')
        {
          if (c1 == c5 && c9 == c5)
          {
            ganar = 1;
          }
          if (c2 == c5 && c8 == c5)
          {
            ganar = 1;
          }
          if (c4 == c5 && c6 == c5)
          {
            ganar = 1;
          }
          if (c3 == c5 && c7 == c5)
          {
            ganar = 1;
          }
        }
        if (c9 == 'X' || c9 == 'O')
        {
          if (c6 == c9 && c3 == c9)
          {
            ganar = 1;
          }
          if (c7 == c9 && c8 == c9)
          {
            ganar = 1;
          }
        }
        //O si hubo un empate
        if ((c1 != '1' && c2 != '2' && c3 != '3' &&
             c4 != '4' && c5 != '5' && c6 != '6' &&
             c7 != '7' && c8 != '8' && c9 != '9') &&
            ganar == 0)
        {
          empate = 1;
        }
        if (ganar == 1 || empate == 1)
        {
          //Si gano el jugador anterior, significa que el jugador actual perdio y se le muestra mensaje de jugar de nuevo
          if (ganar == 1)
          {
            printf("Perdiste \n\n");
            printf("Desea jugar de nuevo?(Y/N)\n\n");
          }
          //O si empato
          if (empate == 1)
          {
            printf("Empate!\n");
            printf("Desea jugar de nuevo?(Y/N)\n\n");
          }
        }
      }
    }
    //Respuesta del jugador actual, en bucle ya que puede equivocarse al escribir
    while (1)
    {
      printf("> ");
      fgets(buf, BUFSIZ, stdin);
      //Respuesta del jugador actual Y/N para seguir jugando o terminar todo
      if (*buf == 'y' || *buf == 'Y')
      {
        jugador = 1, empate = 0, ganar = 0;
        c1 = '1', c2 = '2', c3 = '3', c4 = '4', c5 = '5', c6 = '6', c7 = '7', c8 = '8', c9 = '9', letra = 'X';
        printf("\n letra: %c\n", letra);
        printf("\n %c | %c | %c\n", c1, c2, c3);
        printf("---+---+---\n");
        printf("\n %c | %c | %c\n", c4, c5, c6);
        printf("---+---+---\n");
        printf("\n %c | %c | %c\n\n", c7, c8, c9);
        break;
      }
      else if (*buf == 'n' || *buf == 'N')
      {
        DesbloquearSemaforo(idSem, tuSem);
        exit(0);
      }
      else if (*buf == '1' && c1 == '1')
      {
        c1 = letra;
        break;
      }
      else if (*buf == '2' && c2 == '2')
      {
        c2 = letra;
        break;
      }
      else if (*buf == '3' && c3 == '3')
      {
        c3 = letra;
        break;
      }
      else if (*buf == '4' && c4 == '4')
      {
        c4 = letra;
        break;
      }
      else if (*buf == '5' && c5 == '5')
      {
        c5 = letra;
        break;
      }
      else if (*buf == '6' && c6 == '6')
      {
        c6 = letra;
        break;
      }
      else if (*buf == '7' && c7 == '7')
      {
        c7 = letra;
        break;
      }
      else if (*buf == '8' && c8 == '8')
      {
        c8 = letra;
        break;
      }
      else if (*buf == '9' && c9 == '9')
      {
        c9 = letra;
        break;
      }
      else
      {
        //si no existe el movimiento
        printf("Movimiento no valido\n");
      }
    }
    //Si la respuesta es y entonce termina el turno del jugador actual para poder empezar todo de nuevo
    if (*buf == 'y' || *buf == 'Y')
    {
      ;
    }
    else
    {
      //Se cambia de letra y jugador
      jugador++;
      if (jugador % 2 == 0)
      {
        letra = 'O';
      }
      else
      {
        letra = 'X';
      }
      //Se muestra como queda el tablero del jugador actual que envia el mensaje
      printf("\n letra: %c\n", letra);
      printf("\n %c | %c | %c\n", c1, c2, c3);
      printf("---+---+---\n");
      printf("\n %c | %c | %c\n", c4, c5, c6);
      printf("---+---+---\n");
      printf("\n %c | %c | %c\n\n", c7, c8, c9);

      if (c1 == 'X' || c1 == 'O')
      {
        if (c2 == c1 && c3 == c1)
        {
          ganar = 1;
        }
        if (c4 == c1 && c7 == c1)
        {
          ganar = 1;
        }
      }

      if (c5 == 'X' || c5 == 'O')
      {
        if (c1 == c5 && c9 == c5)
        {
          ganar = 1;
        }
        if (c2 == c5 && c8 == c5)
        {
          ganar = 1;
        }
        if (c4 == c5 && c6 == c5)
        {
          ganar = 1;
        }
        if (c3 == c5 && c7 == c5)
        {
          ganar = 1;
        }
      }

      if (c9 == 'X' || c9 == 'O')
      {
        if (c6 == c9 && c3 == c9)
        {
          ganar = 1;
        }
        if (c7 == c9 && c8 == c9)
        {
          ganar = 1;
        }
      }

      if ((c1 != '1' && c2 != '2' && c3 != '3' &&
           c4 != '4' && c5 != '5' && c6 != '6' &&
           c7 != '7' && c8 != '8' && c9 != '9') &&
          ganar == 0)
      {
        empate = 1;
      }

      if (ganar == 1 || empate == 1)
      {
        if (ganar == 1)
        {
          //Si gano el jugador en ese momento le saldra el mensaje de victoria
          printf("Ganaste !\n\n");
        }

        if (empate == 1)
        {
          //O de empate
          printf("Empate!\n");
        }
      }
    }
    //Se pasa en control al otro usuario
    DesbloquearSemaforo(idSem, tuSem);
    //pregunta si desea salir un jugador
    if (strcmp(buf, "\\quit\n") == 0)
      break;
  }
  //El primer jugador tiene que liberar los semáforos.
  if (miSem == SEM_USER_1)
    BorrarSemaforos(idSem);
}

//funciones
int CrearSemaforos(int n, short *vals)
{
  union semun arg;
  int id;
  id = semget(IPC_PRIVATE, n, SHM_R | SHM_W);
  arg.array = vals;
  semctl(id, 0, SETALL, arg);
  return id;
}
void BorrarSemaforos(int id)
{
  if (semctl(id, 0, IPC_RMID, NULL) == -1)
  {
    perror("Error liberando semáforo!");
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

int ReservarMemoriaComp(int n)
{
  return shmget(IPC_PRIVATE, n, IPC_CREAT | SHM_R | SHM_W);
}
void *MapearMemoriaComp(int id)
{
  void *addr;
  addr = shmat(id, NULL, 0);
  shmctl(id, IPC_RMID, NULL);
  return addr;
}