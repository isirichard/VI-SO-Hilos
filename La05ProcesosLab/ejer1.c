#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(void) {
	int pid;
	printf("Hasta aquí hay un único proceso...\n");
	printf("Primera llamada a fork...\n");
	printf("El pid del programa principal es %d\n", (int) getpid());
	/* Creamos un nuevo proceso. */
	pid = fork();
	if (pid > 0) {
		printf("PADRE: Hola, soy el padre. El pid de mi hijo es: %d\n",pid);
		printf("PADRE: Voy a pararme durante 10 seg. y luego terminaré...\n");
		sleep(10);
	}
	else if (pid == 0) {
		printf("HIJO1: Hola, yo soy el hijo...\n");
		sleep(1);
		/* Creamos un nuevo proceso. */
		pid = fork();
		if (pid == 0) {
			printf("NIETO: Hola, soy el nieto...\n");
			sleep(1);
			printf("NIETO: El nieto va a ejecutar la orden 'ls'...\n");
			execlp("ls","ls",NULL);
			printf("NIETO: Si ve este mensaje, el execlp no funcionó...\n");
		}
		else if (pid > 0) {
			printf("HIJO: Hola otra vez. Pid de mi hijo(el nieto) es : %d\n",pid);
			printf("HIJO: Voy a esperar a que terminen mi padre e hijo(nieto)...\n");
			printf("bye...\n");
		}
		else
			printf("Ha habido algún error al llamar por 2ª vez al fork\n");
	}
	else
		printf("Ha habido algún error al llamar a fork\n");
}
