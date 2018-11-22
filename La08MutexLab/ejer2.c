#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
void *funcionThread(void *parametro);

#define TAMANO_BUFFER 1000
int buffer[TAMANO_BUFFER];

int main(){
	pthread_t idHilo;
	int error;
	int contador;
	int i;

	error=pthread_create(&idHilo,NULL,funcionThread,NULL);
	if (error!=0){
		perror("No puedo crear thread..");
		exit(-1);
	}
	while(1){
		for(i=0;i<TAMANO_BUFFER;i++)
			buffer[i]=contador;
		contador++;
	}
	return 0;
}


void *funcionThread(void *parametro){
	int i;
	int elementoDist=0;
	while(1){
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
	}
}

