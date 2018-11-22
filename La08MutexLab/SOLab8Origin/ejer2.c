#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

int *buffer;
int *tamanoBuffer;
int pos=0;
pthread_mutex_t mutexBuffer = PTHREAD_MUTEX_INITIALIZER;

void *t1(void *arg){
		  pthread_mutex_lock(&mutexBuffer);
		  if(pos == *tamanoBuffer)
					 exit(0);

		  buffer[pos] = pos;
		  printf("Escribi %d en la poscion %d del buffer\n",pos, pos);
		  pos++;
		  sleep(1);
		  pthread_mutex_unlock(&mutexBuffer);
}
void *t2(void *arg){
		  pthread_mutex_lock(&mutexBuffer);
		  if(pos == *tamanoBuffer)
					 exit(0);

		  buffer[pos] = pos;
		  printf("Escribi %d en la poscion %d del buffer\n",pos, pos);
		  pos++;
		  sleep(1);
		  pthread_mutex_unlock(&mutexBuffer);
}
void *t3(void *arg){
		  pthread_mutex_lock(&mutexBuffer);
		  if(pos == *tamanoBuffer)
					 exit(0);

		  buffer[pos] = pos;
		  printf("Escribi %d en la poscion %d del buffer\n",pos, pos);
		  pos++;
		  sleep(1);
		  pthread_mutex_unlock(&mutexBuffer);
}
void *t4(void *arg){
		  pthread_mutex_lock(&mutexBuffer);
		  if(pos == *tamanoBuffer)
					 exit(0);

		  buffer[pos] = pos;
		  printf("Escribi %d en la poscion %d del buffer\n",pos, pos);
		  pos++;
		  sleep(1);
		  pthread_mutex_unlock(&mutexBuffer);
}

int main(){
		  printf("ingrese la cantidad del buffer: \n");
		  int cantidadBuff;
		  scanf("%d", &cantidadBuff);
		  int buf[cantidadBuff];
		  buffer = buf;
		  tamanoBuffer = &cantidadBuff;
		  pthread_t hilo1, hilo2, hilo3, hilo4;
		  int iterar = 0;
		  while(iterar < *tamanoBuffer){
					 if (pthread_create(&hilo1,NULL,t1,NULL)) {
								printf("Error creando el hilo.");
								abort();
					 }
					 if (pthread_create(&hilo2,NULL,t2,NULL)) {
								printf("Error creando el hilo.");
								abort();
					 }
					 if (pthread_create(&hilo3,NULL,t3,NULL)) {
								printf("Error creando el hilo.");
								abort();
					 }
					 if (pthread_create(&hilo4,NULL,t4,NULL)) {

								printf("Error creando el hilo.");
								abort();
					 }
					 iterar++;
		  }
		  pthread_join( hilo1, NULL);
		  pthread_join( hilo2, NULL);
		  pthread_join( hilo3, NULL);
		  pthread_join( hilo4, NULL);

}
