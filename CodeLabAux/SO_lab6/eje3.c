/*
Hecho por: Iam Contreras
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
//Definir una estructura que contendrá los datos de cada tarea
pthread_t hiloTarea[0];
typedef struct
{
    char id[3];
    char desc[50];
    int temp;
    char pre[6];
} tarea;
//Esta función se encarga de leer por pantalla el nombre del fichero comprobar si el fichero existe.

void *thLectura(void *arg)
{
    char *fichero = (char *)arg;
    FILE *archivo = fopen(fichero, "r");

    if (archivo)
    {
        fclose(archivo);
        printf("El archivo existe\n");
    }
    else
    {
        printf("El archivo no existe, se cierra el programa..\n");
        exit(0);
    }
}
/* Esta función se encarga de leer el archivo de texto, y pasar la
información a la memoria (arreglo de tareas).
Devuelve el número de tareas de la actividad.
*/
int leerFichero(char fichero[], tarea listaPasos[])
{
    char ayuda[50];
    FILE *archivo = fopen(fichero, "r");
    char c;
    int contador = 0, aux = 0, contadorGuion = -1;
    while (!feof(archivo))
    {
        c = fgetc(archivo);
        if (c == '-' || c == '\n' || c == EOF)
        {
            ayuda[aux] = '\0';
            aux = 0;
            contadorGuion++;
            if (contadorGuion == 0)
                strcpy(listaPasos[contador].id, ayuda);
            if (contadorGuion == 1)
                strcpy(listaPasos[contador].desc, ayuda);
            if (contadorGuion == 2)
                sscanf(ayuda, "%d", &listaPasos[contador].temp);
            if (contadorGuion == 3)
                strcpy(listaPasos[contador].pre, ayuda);
        }
        else
        {
            if (c != ' ' || c != '\n')
            {
                ayuda[aux] = c;
                aux++;
            }
        }
        if (c == EOF)
        {
            printf("\n\n");
            break;
        }
        if (c == '\n')

        {
            contador++;
            aux = 0;
            contadorGuion = -1;
            memset(ayuda, 0, sizeof ayuda);
            printf("\n");
        }
        else
            printf("%c", c);
    }
    fclose(archivo);
    contador++;
    return contador;
} /* Esta función se encarga de llevar a cabo cada una de las tareas
definidas para la actividad.
Muestra por pantalla cuando inicia la tarea, espera el tiempo que el
fichero indica.
Informa de que ha finalizado la tarea y cierra el hilo.
*/
void *hacerTarea(void *arg)
{
    tarea *tareas = (tarea *)arg;

    if (tareas->pre[1] != '\0')
    {
        int aux = (tareas->pre[1] - '0');
        pthread_join(hiloTarea[aux], NULL); // espera  a que temrine si tiene 1 tarea
    }
    if (tareas->pre[4] != '\0')
    {
        int aux = (tareas->pre[4] - '0');
        pthread_join(hiloTarea[aux], NULL); // espera  a que temrine si tiene 2nd tarea
    }

    printf("Tarea: %s esta ejecutandose ... %d\n", tareas->id, tareas->temp);
    sleep(tareas->temp);
    printf("Tarea: %s TERMINO\n", tareas->id);
}
int main()
{
    // crear un hilo para leer por pantalla el nombre de un fichero y verificar su existencia
    char fichero[50]; //nombre del archivo de 50 caracteres maximo
    printf("Ingrese el nombre del fichero: ");
    scanf("%[^\n]", fichero);

    pthread_t hiloLectura;
    pthread_create(&hiloLectura, NULL, thLectura, (void *)&fichero);
    pthread_join(hiloLectura, NULL);
    // llamar a la funcion que lee el contenido del fichero a un arreglo de Tareas

    tarea tareas[50]; // definimos 50 tareas
    int totalTareas = leerFichero(fichero, tareas);
    printf("Tareas a realizar: %d\n", totalTareas);
    // Para cada tarea de la actividad que no tenga tareas predecesoras
    // crear un hilo, de lo contrario esperar a que estas tareas
    // predecesores terminen para realizar la tarea.

    hiloTarea[totalTareas];
    for (int i = 0; i < totalTareas; i++)
    {
        pthread_create(&hiloTarea[i], NULL, hacerTarea, (void *)&tareas[i]);
    }
    for (int i = 0; i < totalTareas; i++)
    {
        pthread_join(hiloTarea[i], NULL);
    }
}