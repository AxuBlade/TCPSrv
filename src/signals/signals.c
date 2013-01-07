#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include "signals.h"
#include "../defines.h"

void signal_handler(int signo)  {

  volatile unsigned short int* setFlag = (volatile unsigned short int*) &permissionToRunFlag;
  pid_t pid;
  int status;
  
  if(signo == SIGCHLD)  {
    while((pid=waitpid(-1,&status,WNOHANG)) > 0)  {
      printf("## proces PID = %d, STATUS = %s\n", pid, (WEXITSTATUS(status) == 0) ? "Zakonczony poprawnie" : "Zakonczony z bledem");
    }
  }
  if(signo == SIGINT || signo == SIGTERM)  {
    printf("!!!!Przechwycono sygnal %s\n", signo == SIGINT ? "SIGINT" : "SIGTERM");
    fflush(stdout);
    if(*setFlag) *setFlag = 0;
  }


}