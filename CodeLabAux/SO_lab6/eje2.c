/*Hecho por: Iam Contreras*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int global = 0;

void *generador(void *arg)
{
    int hilo = *(int *)arg;
    int numeroRandom = 0;
    for (int i = 0; i < 10; i++)
    {
        numeroRandom = rand() % 100 + 1;
        int dormir = rand() % 3 + 1;
        printf("Hilo %d generando numeros: %d...(%d)\n", hilo, numeroRandom, dormir);
        global = global + numeroRandom;
        sleep(dormir);
    }
}

int main()
{
    srand(time(NULL));
    pthread_t hilos[3];

    for (int i = 0; i < 3; i++)
    {
        pthread_create(&hilos[i], NULL, generador, (void *)&i);
    }
    for (int i = 0; i < 3; i++)
    {
        pthread_join(hilos[i], NULL);
    }
    printf("Numero global: %d\n", global);
    return 0;
}
