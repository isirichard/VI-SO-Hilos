/*
	Richard Alvarez mamani
	Paulo Rodriguez Contreras
*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
void lee();
void escribe();
/*
	Tamaño del arreglo
*/

#define tamanoBuffer 10
int buffer[tamanoBuffer];
/*
	Variable global
*/
int cont = 0;
/*
	Creación del semaforo
*/
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
/*
	variable de condición vacio y lleno
*/
pthread_cond_t condition_varVacio = PTHREAD_COND_INITIALIZER;
pthread_cond_t condition_varLleno = PTHREAD_COND_INITIALIZER;

void *consumidor(void *arg){
/*
	Comprobación del consumidor si vacio se duerme
*/
	pthread_mutex_lock( &mutex );
	if (cont == 0){ 
		printf("buffer vacio, esperando al productor que lo llene\n");
		pthread_cond_wait( &condition_varLleno, &mutex );        	  
	}
/*
	En caso de que no libera
*/
	lee();
	pthread_mutex_unlock( &mutex );
	pthread_cond_signal( &condition_varVacio );
}

void *productor(void *arg){
	/*
		Si esta lleno el productor se duerme
	*/
	pthread_mutex_lock( &mutex );
	if(cont == tamanoBuffer){
		printf("buffer lleno, esperando que el consumidor lo vacie\n");
		pthread_cond_wait( &condition_varVacio, &mutex );
	}	
	/*
		En caso de que no este lleno escribe
	*/
	escribe();
	pthread_mutex_unlock( &mutex );
	pthread_cond_signal( &condition_varLleno );

}

void lee(){
	int i;
	printf("Consumidor esta leendo datos del buffer: ");
	for( i = 0; i < tamanoBuffer; i++)
		printf("%d ", buffer[i]);
	printf("\n");
	sleep(1);
	cont = 0;
}

void escribe(){
	int i;
	printf("Productor esta escribiendo en el buffer\n");
	for( i = 0; i < tamanoBuffer; i++)
		buffer[i] = rand()%10;
	sleep(1);
	cont = tamanoBuffer;
}

int main(){
	pthread_t hiloConsumidor, hiloProductor;

	while(1){
		 /*
			Creación del hilo principal
		 */
		pthread_create(&hiloConsumidor,NULL,consumidor,NULL);
		/*
			Creación del hilo segundo
		 */
		pthread_create(&hiloProductor,NULL,productor,NULL);

		pthread_join( hiloConsumidor, NULL);
		pthread_join( hiloProductor, NULL);
	}
	printf("fin");
}
