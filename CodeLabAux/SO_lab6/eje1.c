/*Ejercicio Matriz - Iam Contreras*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

struct parametros p1; //p1 para que los hilos cojan la matriz

struct parametros
{
    int id;
    float escalar;
    float matriz[3][3];
};
void init(float m[3][3])
{
    int i;
    int j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            m[i][j] = random() * 100;
        }
    }
}
void *matrizporescalar(void *arg)
{
    int hilo = *(int *)arg;
    int i, j;
    int dormir = rand() % 10;

    printf(" Hilo %d multiplicando fila %d...(%d)\n", hilo, hilo, dormir);
    for (j = 0; j < 3; j++)
    {
        p1.matriz[hilo][j] = p1.matriz[hilo][j] * p1.escalar;
    }
    sleep(dormir);
    printf(" Hilo %d TERMINO\n", hilo);
}
int main(int argc, char *argv[])
{
    srand(time(NULL));
    pthread_t h1[3]; //numero de filas de la matriz

    p1.id = 1;
    p1.escalar = 5.0;
    init(p1.matriz);
    for (int i = 0; i < 3; i++) // i<3 por la longitud de la matriz
    {
        pthread_create(&h1[i], NULL, matrizporescalar, (void *)&i); // &i indicando la fila a procesar
    }
    for (int i = 0; i < 3; i++)
    {
        pthread_join(h1[i], NULL);
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%f ",p1.matriz[i][j]);
        }
        printf("\n");
    }
    printf("Fin \n");
}
