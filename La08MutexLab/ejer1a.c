#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_mutex_t s = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t t = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t v = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t conA = PTHREAD_COND_INITIALIZER;;
pthread_cond_t conB = PTHREAD_COND_INITIALIZER;;
pthread_cond_t conC = PTHREAD_COND_INITIALIZER;;

void *funcion01(void *arg) {
    int i;

    while(1){
        pthread_mutex_lock(&s);
        
        for (i=0; i<20; i++) {
            printf("+");
            fflush(stdout);
        /*sleep(1);*/
        }
        
        
        pthread_mutex_unlock(&t);
        /*pthread_cond_signal(&conB);*/
        /*pthread_cond_wait(&conA,&s);*/
       

    }
    return NULL;
}
void *funcion02(void *arg) {
    int i;
    while(1){
        pthread_mutex_lock(&v);
        /*pthread_cond_wait(&conC, &v);*/
        for (i=0; i<20; i++) {
            printf("o");
            fflush(stdout);
        /*sleep(1); */
        }

        
        pthread_mutex_unlock(&s);
        /*pthread_cond_signal(&conA);*/
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
    while(1){
        pthread_mutex_lock(&t);
        /*pthread_cond_wait(&conB, &v);*/
        for (i=0; i<20; i++) {
            printf("x");
            fflush(stdout);
        /* sleep(3); */
        }

        
        pthread_mutex_unlock(&v);
        /*pthread_cond_signal(&conC);*/
    }
    pthread_join(mihilo01, NULL);
    pthread_join(mihilo02, NULL);
    
    exit(0);
}
