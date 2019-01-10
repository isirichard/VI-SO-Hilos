//Hecho por Iam Contreras Alcazar
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define TAMBUFFER 200 //definimos un buffer grande para que ver mejor los resultados

int buffer[TAMBUFFER];
int cont = 0;
char vacio = 1, lleno = 0; // variables de ayuda condicionales
pthread_mutex_t mutex; // semaforo
pthread_cond_t condicionProductor, condicionConsumidor; // variables condicionales

void escribe(); 
void lee();

void *productor(void *args)
{
  while (1)
  {
    //inicio de seccion critica
    pthread_mutex_lock(&mutex);
    if (lleno == 1)// en caso que este lleno el buffer se duerme el productor
    {
      printf("\nLleno me duermo\n\n");

      pthread_cond_signal(&condicionConsumidor);// despertamos al consumidor
      pthread_cond_wait(&condicionProductor, &mutex);// se duerme el productor
    }
    escribe();// funcion que agrega al buffer para producir
    pthread_mutex_unlock(&mutex);
    //fin de seccion critica;
  }
}

int main()
{
  srand(time(NULL));  // semilla para los numeros random del productor
  //incializamos mutex y variables condicionales
  pthread_mutex_init(&mutex, NULL); 
  pthread_cond_init(&condicionProductor, NULL);
  pthread_cond_init(&condicionConsumidor, NULL);
  pthread_t hilo;
  //creamos el hilo productor
  pthread_create(&hilo, NULL, productor, NULL);

  //inicio del hilo principal que viene a ser el consumidor
  while (1)
  {
    //inicio de seccion critica
    pthread_mutex_lock(&mutex);
    if (vacio == 1) // En caso que este vacio el buffer no se puede consumir
    {
      printf("\nNo puedo consumir me duermo\n\n");
      pthread_cond_signal(&condicionProductor);//despertamos al productor 
      pthread_cond_wait(&condicionConsumidor, &mutex); // se duerme el consumidor
    }
    lee();//funcion para leer y consumir
    pthread_mutex_unlock(&mutex);
    //fin de seccion critica
  }

  return 0;
}

void escribe()
{
  
  printf("Produciendo...");
  
  buffer[cont] = rand() % 10 + 1;// valor random del productor
  printf(" (posicion %d) valor: %d\n", cont, buffer[cont]);
  cont++;

  vacio = 0;// al producir cambiamos el estado de vacio a 0 indicando que no esta vacio
  pthread_cond_signal(&condicionConsumidor);// si no esta vacio se puede consumir
  if (cont == TAMBUFFER)// si el buffer esta completo cambiamos lleno a 1 para no producir mas
    lleno = 1;// se verifica en el hilo del productor
}

void lee()
{
  cont--;// descontamos para leer el buffer ya que tiene 1+
  printf("Comiendo (posicion %d) valor: %d\n", cont, buffer[cont]);
  
  buffer[cont] = 0;// se vacia el producto en la posicion cont
  lleno = 0;//se cmabia el estado lleno ya que no esta completo el buffer
  pthread_cond_signal(&condicionProductor);// si no esta completo el buffer se puede producir mas
  if (cont == 0)// si el cont es 0 indica que esta vacio el buffer y se debe producir
  {
    vacio = 1;// cambiamos el el valor vacio que se verifica en el hilo principal del consumidor
  }
}