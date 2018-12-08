#include <string.h>
#include <stdio.h>
#include <stdint.h>

typedef struct {
	char nombre[30];
	char e_mail[30];
	int edad;
	char *buf;
	enum {
		usadoH,
		usadoM,
		vacio
	} varCartel;
}varCompartida;

typedef struct {
	char buf[50];
	int sema;
	enum {
		usandoH,
		usandoM,
		usadoVacio
	}cartel;
	enum {
		colaH,
		colaM,
		colaVacio
	}cola;
}varProcesos;


int main(int argc, char* argv[]){
	if(strcmp("H", argv[2])==0){
		printf("El char buf es:%s\n",argv[2]);
	}
	
	char colaSH[] = {"MMMHMMHM"};
	int i;
	for (i = 0; i < sizeof(colaSH); i++)
		printf("%c ", colaSH[i]);
	printf("=> ");
	printf("\n");
	fflush(stdout);
	for (i = sizeof(colaSH); i >=0 ; i--)
		printf("%c ", colaSH[i]);
	if('M'== colaSH[0])
		printf("el primer elemento es: M\n");
	

	printf("El char buf es:%s\n",argv[2]);
	/*
	varCompartida var = {"richard","isirichard@",28,"variable",usadoM};
	varCompartida *ptr = &var; 
	printf("El nombre es: %s\n",ptr->nombre );
	printf("El e-mail es: %s\n",ptr->e_mail );
	printf("La edad es: %d\n",ptr->edad );
	printf("El buf es: %s\n",ptr->buf );
	ptr->varCartel=vacio;
	printf("El cartel es: %d\n",ptr->varCartel );
	*/
	varProcesos var = {"richard",1234567,usadoVacio,usadoVacio};
	varProcesos *ptr = &var; 
	printf("El char buf es: %s\n",ptr->buf );
	printf("El id sema es: %d\n",ptr->sema );
	printf("El enum id cartel es: %d\n",ptr->cartel );
	printf("El enum id cola es: %d\n",ptr->cola );


	return 0;

}