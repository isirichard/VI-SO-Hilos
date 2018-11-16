//sigusr1.c
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
sig_atomic_t sigterm_contador = 0;
void manejador(int nro_senal){
	++sigterm_contador;
	printf("SIGTERM se dio %d veces\n", sigterm_contador);
}

int main()
{
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &manejador;
	sigaction(SIGTERM, &sa, NULL);
	
	while(1);
	return 0;
}
