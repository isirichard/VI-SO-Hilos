/*
    Richard Alvarez mamani
    Paulo Rodriguez Contreras
*/
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
/*
    Creación de tres semaforos
*/
pthread_mutex_t s = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t t = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t v = PTHREAD_MUTEX_INITIALIZER;

/*
    Las dos siguientes funciones imprimien pero son controladas por los tres semaforos
    No terminan su ejecución, sólo imprimen en un orden establecido
*/
void *funcion01(void *arg) {
    int i;

    while(1){
        pthread_mutex_lock(&s);
        
        for (i=0; i<20; i++) {
            printf("+");
            fflush(stdout);
        } 
        pthread_mutex_unlock(&t);
       
    }
    return NULL;
}
void *funcion02(void *arg) {
    int i;
    while(1){
        pthread_mutex_lock(&v);
        for (i=0; i<20; i++) {
            printf("o");
            fflush(stdout);
        }

        
        pthread_mutex_unlock(&s);
    }
    return NULL;
}
int main() {
    pthread_t mihilo01, mihilo02;
    int i;
    
    if (pthread_create(&mihilo01,NULL,funcion01,NULL)) {
        printf("Error creando el hilo.");
        abort();
    }

    if (pthread_create(&mihilo02,NULL,funcion02,NULL)) {
        printf("Error creando el hilo.");
        abort();
    }
    /*
        Este hilo principal es parte de la impresión controlado por los tres mutex
    */
    while(1){
        pthread_mutex_lock(&t);
        for (i=0; i<20; i++) {
            printf("x");
            fflush(stdout);
        }      
        pthread_mutex_unlock(&v);

    }
    pthread_join(mihilo01, NULL);
    pthread_join(mihilo02, NULL);
    
    exit(0);
}
