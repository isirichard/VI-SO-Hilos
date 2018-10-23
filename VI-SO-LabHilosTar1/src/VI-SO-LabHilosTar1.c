/*Ejercicio Matriz */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
int fila = 0;
struct parametros {
	int id;
	float escalar;
	float matriz[3][3];
};
void init(float m[3][3]) {
	int i;
	int j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			//m[i][j] = random() * 100;
			m[i][j] = i+j;
		}
	}
}
void* matrizporescalar(void *arg) {
	struct parametros *p;
	int i;
	int j;
	p = (struct parametros *) arg;
	/*
	for (i = 0; i < 3; i++) {
		printf(" Hilo %d multiplicando fila %d\n", p->id, i);
		for (j = 0; j < 3; j++) {
			p->matriz[i][j] = p->matriz[i][j] * p->escalar;
			//sleep(1);
		}
	}
	*/
	for (j = 0; j < 3; j++) {
		p->matriz[fila][j] = p->matriz[fila][j] * p->escalar;
		//sleep(1);
	}
	fila++;
}

void* matrizmostrar(void *arg) {
	struct parametros *p;
	int i;
	int j;
	p = (struct parametros *) arg;
	for (i = 0; i < 3; i++) {
		//printf(" Hilo %d multiplicando fila %d\n", p->id, i);
		printf("\n");
		for (j = 0; j < 3; j++) {
			//p->matriz[i][j] = p->matriz[i][j] * p->escalar;
			printf("%1.0f ", p->matriz[i][j]);
			//sleep(1);
		}
	}
	printf("\n");
}

int main(int argc, char *argv[]) {

	pthread_t h1;
	pthread_t h2;
	pthread_t h3;
	struct parametros p1;
	p1.id = 1;
	p1.escalar = 2;
	init(p1.matriz);
	pthread_create(&h1, NULL, matrizporescalar, (void *) &p1);
	pthread_join(h1, NULL);
	pthread_create(&h2, NULL, matrizporescalar, (void *) &p1);
	pthread_join(h1, NULL);
	pthread_create(&h3, NULL, matrizporescalar, (void *) &p1);
	pthread_join(h1, NULL);


	pthread_create(&h1, NULL, matrizmostrar, (void *) &p1);
	pthread_join(h1, NULL);
	printf("Fin \n");
}

