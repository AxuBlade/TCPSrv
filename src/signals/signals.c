#include "signals.h"
#include "../defines.h"

#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

void signal_handler(int signo)  {

  volatile unsigned short int* setFlag = (volatile unsigned short int*) &permissionToRunFlag;
  pid_t pid;
  int status;
  
  if (signo == SIGCHLD)  {
    while ((pid=waitpid(-1,&status,WNOHANG)) > 0)  {
      printf("## proces PID = %d, STATUS: %s\n", pid, (WEXITSTATUS(status) == 0) ? "Zakonczony poprawnie" : "Zakonczony z bledem");
      fflush(stdout);
    }
  }
  if ((signo == SIGINT) || (signo == SIGTERM))  {
    printf("!!!! Proces PID = %d: Przechwycono sygnal %s\n", getpid(), signo == SIGINT ? "SIGINT" : "SIGTERM");
    fflush(stdout);
    if (*setFlag) *setFlag = 0;
  }

}