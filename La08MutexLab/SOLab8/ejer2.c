/*
	Richard Alvarez mamani
	Paulo Rodriguez Contreras
*/
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

/*
	Declarando buffer y el tamaño y posición globales para la utilización en hilos
*/
int *buffer;
int *tamanoBuffer;
int pos=0;
/*
	Semaforo que regula acceso a escritura al buffer
*/
pthread_mutex_t mutexBuffer = PTHREAD_MUTEX_INITIALIZER;
/*
	Primer Hilo
*/
void *t1(void *arg){
	/*
		Preguntar si llego al limite
	*/
	pthread_mutex_lock(&mutexBuffer);
	if(pos == *tamanoBuffer)
		exit(0);

	buffer[pos] = pos;
	printf("Escribi %d en la poscion %d del buffer\n",pos, pos);
	pos++;
	sleep(1);
	pthread_mutex_unlock(&mutexBuffer);
}
/*
	Segundo Hilo
*/
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
/*
	Tercer Hilo
*/
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
/*
	Cuarto Hilo
*/
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

int main(int argc, char *argv[]){

	/*
		Recibiendo parametro desde prinft y scanf
	*/
	printf("ingrese la cantidad del buffer: \n");
	int cantidadBuff;
	scanf("%d", &cantidadBuff);
	int bufEst[cantidadBuff];
	buffer = bufEst;
	tamanoBuffer = &cantidadBuff;

	/*
		Creando hilos
	*/
	pthread_t hilo1, hilo2, hilo3, hilo4;

	int contador = 0;
	/*
		Contar hasta que no haya espacio en el buffer o llegue al limite
	*/
	while(contador < *tamanoBuffer){
		pthread_create(&hilo1,NULL,t1,NULL);
		pthread_create(&hilo2,NULL,t2,NULL);
		pthread_create(&hilo3,NULL,t3,NULL);
		pthread_create(&hilo4,NULL,t4,NULL);
		
		contador++;
	}
	/*
		Esperando a que los hilos terminen
	*/
	pthread_join( hilo1, NULL);
	pthread_join( hilo2, NULL);
	pthread_join( hilo3, NULL);
	pthread_join( hilo4, NULL);

}
