/*semaforo_2.c
  Gerald Zea
  Iam Contreras
  ejecutar antes de agente
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
  arg.val = 0;
  semctl(idSemaforo, 0, SETVAL, &arg);
  operacion.sem_num = 1;
  operacion.sem_op = -1;
  operacion.sem_flg = 0;
  while (1)
  {
    printf("FUMADOR PAPEL semaforo \n");
    semop(idSemaforo, &operacion, 1);
    printf("Salgo del semaforo FUMADOR PAPEL\n");
    
  }
}