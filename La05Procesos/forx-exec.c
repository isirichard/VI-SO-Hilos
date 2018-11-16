
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int crear(char* programa, char** argumentos)
{
	pid_t pid_hijo;
	pid_hijo = fork();
	if(pid_hijo!=0)
	{
	/*estamos en el padre*/
		return pid_hijo;
	}
	else
	{
	/*estamos en el hijo*/
		execvp(programa, argumentos);
	/*execvp SOLO retorna si hay ERROR*/
		fprintf(stderr, "se dio un error");
		abort();
	}
}
int main(){
	/*la lista de argumentos a pasarle a nuestra función*/
	char* argumentos[] = {
		"ls", /*argv[0], el nombre del programa*/
		"-lh",
		"/",
		NULL /*la lista debe terminar en NULL*/
	};
	/*creamos un proceso hijo que ejecuta el comando "ls"*/
	/*ignoramos el pid retornado*/
	crear("ls", argumentos);
	return 0;
}