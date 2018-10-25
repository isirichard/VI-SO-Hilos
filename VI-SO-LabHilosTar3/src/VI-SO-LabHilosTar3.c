/*
 ============================================================================
 Name        : VI-SO-LabHilosTar3.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
FILE *fd;

/*Definir una estructura que contendrá los datos de cada tarea
 */
typedef struct {
	char id[3];
	char desc[50];
	int temp;
	char pre[6];

} plato;

/*Esta función se encarga de leer por pantalla el nombre del fichero
 y comprobar si el fichero existe.
 */

void *thLectura(void *arg) {
	char direccion[] = "lista.txt";
	fd = fopen(direccion, "rt");
	if (fd == NULL) {
		printf("Error al tratar de leer el archivo (No existe)");
	}

	printf("Si Existe el archivo");
	fclose(fd);
};
/* Esta función se encarga de leer el archivo de texto, y pasar la
 información a la memoria (arreglo de tareas).
 Devuelve el número de tareas de la actividad.
 */
int leerFichero(char fichero[], plato llistaPasos[]) { //plato
	int c; //lectura de caracteres
	int numTarea; //número de tarea del arreglo llistaPasos del estructure plato
	int i, j, k, l; //Contadores para guardar los argumentos
	char espera[10];
	char direccion[] = "lista.txt";//es el fichero que se ingresa

	fd = fopen(direccion, "rt");
	while ((c = fgetc(fd)) != EOF) {
		//primer argumento guardado
		while (c != '-') {
			llistaPasos[numTarea].id[i] = c;
			i++;
		}
		llistaPasos[numTarea].id[i] = '\0';

		//Descripción
		while (c != '-') {
			llistaPasos[numTarea].desc[j] = c;
			j++;
		}
		llistaPasos[numTarea].desc[j] = '\0';

		//Tiempo de espera
		while (c != '-' && c != '\n') {
			espera[k] = c;
			k++;
		}
		llistaPasos[numTarea].temp = atoi(espera);

		if (c == '\n') {
			numTarea++;
		} else {
			l = 0;
			while (c != '\n') {
				if (c != '+' && c != 'T') {
					llistaPasos[numTarea].pre[l] = c;
					l++;
				}
			}
			llistaPasos[numTarea].pre[l] = '\0';
			numTarea++;
		}
	}
	fclose(fd);
	while(numTarea){
		printf("%s",llistaPasos[numTarea].id);
		numTarea--;
	}
};

/* Esta función se encarga de llevar a cabo cada una de las tareas
 definidas para la actividad.
 Muestra por pantalla cuando inicia la tarea, espera el tiempo que el
 fichero indica.
 Informa de que ha finalizado la tarea y cierra el hilo.
 */

void *hacerTarea(void *arg) {
};

int main() {
	printf("prueba");
	//plato lista[20];
	//char fichero[20];
	//leerFichero(lista,fichero);
// crear un hilo para leer por pantalla el nombre de un fichero y
// verificar su existencia
	pthread_t h1;
	pthread_create(&h1, NULL, thLectura, NULL);
	pthread_join(h1, NULL);
// llamar a la funcion que lee el contenido del fichero a un arreglo de
// Tareas
// Para cada tarea de la actividad que no tenga tareas predecesoras
// crear un hilo, de lo contrario esperar a que estas tareas
// predecesores terminen para realizar la tarea.

	pthread_t h2;
	pthread_t h3;
	int c;

	pthread_create(&h2, NULL, hacerTarea, NULL);
	pthread_join(h1, NULL);
	pthread_join(h2, NULL);
	printf("Fin\n");
}
