#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#define tamanoBuffer 15
int *buffer[tamanoBuffer];
int cont = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_varVacio = PTHREAD_COND_INITIALIZER;
pthread_cond_t condition_varLleno = PTHREAD_COND_INITIALIZER;

void *consumidor(void *arg){
/*
Primero veremos el contador que indica la cantidad de elementos que hay en el buffer, si esta vacia esperamos a que se productor lo llene y lo dormimos con un wait	
*/
		  pthread_mutex_lock( &mutex );
		  if (cont == 0){ 
					 printf("buffer vacio, esperando al productor que lo llene\n");
					 pthread_cond_wait( &condition_varLleno, &mutex );        	  
		  }
/*
Una el productor lo llene y despierte al consumidor, empezaremos a ejecutar la lectura
*/
		  lee();
		  pthread_mutex_unlock( &mutex );
		  pthread_cond_signal( &condition_varVacio );
}

void *productor(void *arg){
		  pthread_mutex_lock( &mutex );
		  if(cont == tamanoBuffer){
					 printf("buffer lleno, esperando que el consumidor lo vacie\n");
					 pthread_cond_wait( &condition_varVacio, &mutex );
		  }
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
					 if (pthread_create(&hiloConsumidor,NULL,consumidor,NULL)) {
								printf("Error creando el hilo.");
								abort();
					 }
					 if (pthread_create(&hiloProductor,NULL,productor,NULL)) {
								printf("Error creando el hilo.");
								abort();
					 }
					 pthread_join( hiloConsumidor, NULL);
					 pthread_join( hiloProductor, NULL);
		  }
		  printf("fin");
}
