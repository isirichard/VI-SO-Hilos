
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
	pid_t pid_hijo;
	printf("El pid del programa principal es %d\n", (int) getpid());
	pid_hijo = fork();
	if(pid_hijo!=0)
	{
		printf("Este es el proceso padre con ID %d\n", (int) getpid());
		printf("El ID del hijo es %d\n", (int) pid_hijo);
	}
	else
		printf("Este es el proceso hijo, con ID %d\n", (int) getpid());
}