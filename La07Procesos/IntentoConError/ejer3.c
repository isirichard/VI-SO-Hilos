#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

void captura(int sig);
pid_t Fork(void);
void unix_error(char *msg);
int control=0;
static int received = 0;

void readUsual(int sig)
{
    if (sig == SIGUSR1)
    {
        received = 1;
    }
}
int main()
{
    signal(SIGUSR1,readUsual);
    int status;
    pid_t pid;
    if((pid = Fork()) != 0)
    {
        while(!control) {};
        wait(&status);
        printf("terminaron mis hijos ahora acabo yo....\n");
        exit(0);
    }else  {
        
        printf("\nsoy el hijo mi PID:%d y el de mi padre PID:%d\n",getpid(),getppid());
	int i;
        for(i=20;i>0;i--)
        {
            sleep(1);
            printf("\ntiempo para la señal %d ",i);
        }
	printf("\nesperando señal de user1 \n");
	while (!received)
            ;
        printf("SIGUSR1 received.\n");
        
        printf("\nsoy el hijo mi PID:%d y el de mi padre PID:%d\n",getpid(), getppid());
        exit(0);
    }
    return 0;
}

void captura(int sig)
{
    if( sig == 17)
        control=1;
}

void unix_error(char *msg)
{
    fprintf(stdout, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

pid_t Fork(void) {
  pid_t pid;
  if ((pid = fork()) < 0) 
    unix_error("Fork Error");
  return pid;
}
