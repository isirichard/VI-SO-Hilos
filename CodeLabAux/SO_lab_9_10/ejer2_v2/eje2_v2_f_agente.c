/*semaforo_2.c
  Gerald Zea
  Iam Contreras
  Agente de los fumadores f1_tabaco, f2_papel, f3_cerilla
*/
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
main()
{
  key_t clave;
  int idSemaforo;
  struct sembuf operacion;
  union semun arg;
  int i = 0;
  clave = ftok("/bin/ls", 33);
  
  while (1)
  {
    sleep(1); //el agente se demora en elegir
    int faltante = rand() % 3 + 1;
    if (faltante == 1)
    { //FALTA TABACO
      printf("\nagente coloco papel y cerillas\n");

      if (clave == (key_t)-1)
      {
        printf("No puedo conseguir la clave de semaforo\n");
        exit(0);
      }
      idSemaforo = semget(clave, 10, 0600 | IPC_CREAT);
      if (idSemaforo == -1)
      {
        printf("No puedo crear el semaforo\n");
        exit(0);
      }
      operacion.sem_num = 0;
      operacion.sem_op = 1;
      operacion.sem_flg = 0;
      printf("Levanto semaforo a TABACO\n");
      semop(idSemaforo, &operacion, 1);
      sleep(1);
    }
    else if (faltante == 2)
    { //FALTA PAPEL
      printf("\nagente coloco tabaco y cerillas\n");
      if (clave == (key_t)-1)
      {
        printf("No puedo conseguir la clave de semaforo\n");
        exit(0);
      }
      idSemaforo = semget(clave, 10, 0600 | IPC_CREAT);
      if (idSemaforo == -1)
      {
        printf("No puedo crear el semaforo\n");
        exit(0);
      }
      operacion.sem_num = 1;
      operacion.sem_op = 1;
      operacion.sem_flg = 0;

      printf("Levanto semaforo a PAPEL\n");
      semop(idSemaforo, &operacion, 1);
      sleep(1);
    }
    else if (faltante == 3)
    { //FALTA CERILLAS
      printf("\nagente coloco tabaco y papel\n");
      if (clave == (key_t)-1)
      {
        printf("No puedo conseguir la clave de semaforo\n");
        exit(0);
      }
      idSemaforo = semget(clave, 10, 0600 | IPC_CREAT);
      if (idSemaforo == -1)
      {
        printf("No puedo crear el semaforo\n");
        exit(0);
      }
      operacion.sem_num = 2;
      operacion.sem_op = 1;
      operacion.sem_flg = 0;
      printf("Levanto semaforo a CERILLA\n");
      semop(idSemaforo, &operacion, 1);
      sleep(1);
    }
  }
}