/*
    Richard Alvarez mamani
    Paulo Rodriguez Contreras
*/
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

/*
    Limite de impresion para decrementar
*/
int i = 20;
/*
    Respaldo de la variable anterior
*/
int aux = 20;

/*
    función para imprimir deacuerdo al límite
*/
void *funcion01(void *arg) {

    char pr = (char) arg;
    for (; i > 0; i--) {
        printf("%c", pr);
        fflush(stdout);
    }
    printf("\t %d\n",aux);
    i = --aux;
    return NULL;
}

int main() {
    /* 
        Proceso /Hilo Main
    */

    char letraX ='x';
    char letraO = 'o';
    while (i >= 0) {
        /*
            Creación de dos hilos para imprimir deacuerdo al límite y deacuerdo al orden establecido
            X-O-+
        */
        pthread_t mihilo02, mihilo03;

        pthread_create(&mihilo02, NULL, funcion01, (void *)letraX);
        pthread_join(mihilo02, NULL);

        pthread_create(&mihilo03, NULL, funcion01, (void *)letraO);
        pthread_join(mihilo03, NULL);
        for (; i > 0; i--) {
            printf("+");
            fflush(stdout);
        }
        printf("\t %d\n",aux);
        i = --aux;
    }

    exit(0);
}
