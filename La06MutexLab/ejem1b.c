#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
void *funcionThread(void *parametro);


#define TAMANO_BUFFER 1000
int buffer[TAMANO_BUFFER];
pthread_mutex_t mutexBuffer;



int main(){
	pthread_t idHilo;
	int error;
	int contador;
	int i;
	pthread_mutex_init(&mutexBuffer,NULL);
	error=pthread_create(&idHilo,NULL,funcionThread,NULL);
	if (error!=0){
		perror("No puedo crear thread..");
		exit(-1);
	}
	while(1){
		pthread_mutex_lock(&mutexBuffer);
		for(i=0;i<TAMANO_BUFFER;i++){
			buffer[i]=contador;
		}
		pthread_mutex_unlock(&mutexBuffer);
		contador++;
	}
	return 0;
}


void *funcionThread(void *parametro){
	int i;
	int elementoDist=0;
	while(1){
		pthread_mutex_lock(&mutexBuffer);
		for(i=0;i<TAMANO_BUFFER;i++){
			if (buffer[0]!=buffer[i]){
				elementoDist=1;
				break;
			}
		}
		if (elementoDist){
			printf("Hijo: Error. Elementos distintos en el buffer\n");
		}
		else{
			printf("Hijo: Correcto\n");
		}
		pthread_mutex_unlock(&mutexBuffer);
	}
}

