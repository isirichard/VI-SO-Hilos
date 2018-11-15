#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t conA = PTHREAD_COND_INITIALIZER;;
pthread_cond_t conB = PTHREAD_COND_INITIALIZER;;
pthread_cond_t conC = PTHREAD_COND_INITIALIZER;;

void *funcion01(void *arg) {
    int i;
    for (i=0; i<20; i++) {
        printf("+");
        fflush(stdout);
        //sleep(1);
    }
    pthread_cond_signal(&conA);

    return NULL;
}
void *funcion02(void *arg) {
    int i;
    pthread_cond_wait(&conB, &mutex2);
    for (i=0; i<20; i++) {
        printf("o");
        fflush(stdout);
        //sleep(1);
    }
    return NULL;
}
int main() {

    pthread_t mihilo01, mihilo02;

    int i;
while(1){
    if (pthread_create(&mihilo01,NULL,funcion01,NULL)) {
        printf("Error creando el hilo.");
        abort();
    }
    if (pthread_create(&mihilo02,NULL,funcion02,NULL)) {
        printf("Error creando el hilo.");
        abort();
    }

    pthread_cond_wait(&conA, &mutex);
    for (i=0; i<20; i++) {
        printf("x");
        fflush(stdout);
        // sleep(3);
    }
    pthread_cond_signal(&conB);
    pthread_join(mihilo01, NULL);
    pthread_join(mihilo02, NULL);
}
    exit(0);
}
