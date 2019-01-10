//Hecho por Iam Contreras Alcazar
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>


int buffer[0];
int p = 0; //posicion que recorre el buffer
int TAMBUFFER;
pthread_mutex_t m1;

void *escribir(void *args)
{
  int i = (int *)args; //guardo el i dependiendo del hilo
  while (1)
  {
    sleep(i); //se escribira el hilo luego de i segundos
    //inicio de seccion critica
    pthread_mutex_lock(&m1);
    if (p == TAMBUFFER) //si el buffer esta lleno entonce termina el hilo
    {
      pthread_mutex_unlock(&m1);
      break;
    }
    buffer[p] = i; //numero i
    p++;
    printf("Imprimi un i(%d) en la posicion p(%d) del buffer\n", i, p); //mensaje
    pthread_mutex_unlock(&m1);
    //fin seccion critica
  }
}

int main(int argc, char *argv[])
{
  if(argc!=2){
    printf("ingrese cantidad del buffer\n");
    exit(0);
  }
  sscanf(argv[1], "%d", &TAMBUFFER);//asigno el tamanio del buffer

  buffer[TAMBUFFER];
  pthread_mutex_init(&m1, NULL);
  pthread_t h1, h2, h3, h4;
  //se crean los hilos, se envia de parametro i que viene hacer el numero del hilo
  pthread_create(&h1, NULL, escribir, (void *)1);
  pthread_create(&h2, NULL, escribir, (void *)2);
  pthread_create(&h3, NULL, escribir, (void *)3);
  pthread_create(&h4, NULL, escribir, (void *)4);
  //se esperan a que terminen
  pthread_join(h1, NULL);
  pthread_join(h2, NULL);
  pthread_join(h3, NULL);
  pthread_join(h4, NULL);
  //impresion para ver como quedo el buffer
  for (int i = 0; i < TAMBUFFER; i++)
  {
    printf("%d ", buffer[i]);
  }
  printf("\n");
  return 0;
}