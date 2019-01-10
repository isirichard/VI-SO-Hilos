/*semaforo_2.c
  Gerald Zea
  Iam Contreras
*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

int CrearSemaforos(int n, short *vals);
void BorrarSemaforos(int id);
void BloquearSemaforo(int id, int i);
void DesbloquearSemaforo(int id, int i);

enum {SEM_FUMADOR1, SEM_FUMADOR2, SEM_FUMADOR3, SEM_AGENTE};

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *_buf;
};

int main () {
	printf("INICIO DEL PROGRAMA :)\n");
	srand(time(NULL));
	short vals[4] = {0, 0, 0, 0};
	int idSem = CrearSemaforos(4, vals);
	//el hilo principal es el agente
	pid_t fumador[3];
	fumador[0] = fork();
	if (fumador[0] == 0) {
		//FUMADOR 1
		printf("fumador 1 tiene tabaco\n");
		while (1) {
			BloquearSemaforo(idSem, SEM_FUMADOR1);
			printf("fumador 1 se prepara su cigarro\n");
      DesbloquearSemaforo(idSem, SEM_AGENTE);
		}
	} else {
		fumador[1] = fork();
		if(fumador[1] == 0) {
			//FUMADOR 2
      printf("fumador 2 tiene papel\n");
      while (1) {
        BloquearSemaforo(idSem, SEM_FUMADOR2);
        printf("fumador 2 se prepara su cigarro\n");
        DesbloquearSemaforo(idSem, SEM_AGENTE);
      }
    } else {
      fumador[2] = fork();
      if (fumador[2] == 0) {
        //FUMADOR 3
        printf("fumador 3 tiene cerillas\n");
        while (1) {
          BloquearSemaforo(idSem, SEM_FUMADOR3);
          printf("fumador 3 se prepara su cigarro\n");
          DesbloquearSemaforo(idSem, SEM_AGENTE);
        }
      } else {
        //AGENTE
        usleep(1000);
        int faltante;
        printf("agente tiene tabaco, papel y cerillas\n");
        while(1) {
          sleep(1);	//el agente se demora en elegir
          faltante = rand()%3 + 1;
          if (faltante == 1) {	//FALTA TABACO
            printf("\nagente coloco papel y cerillas\n");
            DesbloquearSemaforo(idSem, SEM_FUMADOR1);
            BloquearSemaforo(idSem, SEM_AGENTE);
          } else if (faltante == 2) {	//FALTA PAPEL
            printf("\nagente coloco tabaco y cerillas\n");
            DesbloquearSemaforo(idSem, SEM_FUMADOR2);
            BloquearSemaforo(idSem, SEM_AGENTE);
          } else if (faltante == 3) {	//FALTA CERILLAS
            printf("\nagente coloco tabaco y papel\n");
            DesbloquearSemaforo(idSem, SEM_FUMADOR3);
            BloquearSemaforo(idSem, SEM_AGENTE);
          }
        }
      }
    }
  }
  BorrarSemaforos(idSem);
}

int CrearSemaforos(int n, short* vals) {
  int id = semget(IPC_PRIVATE, n, SHM_R | SHM_W);
  if (id == -1) {printf("No puedo crear el semaforo\n"); exit(EXIT_FAILURE);}
  union semun arg;
  arg.array = vals;
  if(semctl(id, 0, SETALL, arg) == -1) {perror("Error creando semáforo!"); exit(EXIT_FAILURE);}
  return id;
}

void BorrarSemaforos(int id) {
  if(semctl(id, 0, IPC_RMID, NULL) == -1) {perror("Error liberando semáforo!"); exit(EXIT_FAILURE);}
}

void BloquearSemaforo(int id, int i) {
  struct sembuf sb;
  sb.sem_num = i;
  sb.sem_op = -1;
  sb.sem_flg = SEM_UNDO;
  semop(id, &sb, 1);
}

void DesbloquearSemaforo(int id, int i) {
  struct sembuf sb;
  sb.sem_num = i;
  sb.sem_op = 1;
  sb.sem_flg = SEM_UNDO;
  semop(id, &sb, 1);
}
