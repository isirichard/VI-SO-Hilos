#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void tratasenial (int);
main (){
	pid_t idProceso;
	idProceso = fork();
	if(idProceso==-1) {
		perror("Nose puede lanzar proceso");
	}
	if(idProceso==0){
		signal(SIGUSR1,tratasenial);
		while(1)
			pause();
	}

	if(idProceso>0){
		while(1){
			//cout<<getpid<<endl;
			sleep(1);
			kill(idProceso,SIGUSR1);
		}

	}
}
void tratasenial(int nsenial){
	printf("Recibida las señal del padre \n");
}