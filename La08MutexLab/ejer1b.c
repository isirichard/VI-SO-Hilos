#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>


pthread_mutex_t s = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t t = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t v = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t conA = PTHREAD_COND_INITIALIZER;
pthread_cond_t conB = PTHREAD_COND_INITIALIZER;
pthread_cond_t conC = PTHREAD_COND_INITIALIZER;

int i = 20;
int aux = 20;
struct parametros {
    char matriz[3];
};

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
    struct parametros p1;
    p1.matriz[0] = 'x';
    p1.matriz[1] = 'o';
    p1.matriz[2] = '+';
    char letraX ='x';
    char letraO = 'o';
    while (i >= 0) {
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
