#include "../defines.h"

void signal_handler(int signo)  {

  pid_t pid;
  int status;

  if(signo == SIGCHLD)  {
    while((pid=waitpid(-1,&status,WNOHANG)) > 0)  {
      printf("proces PID = %d, STATUS = %s\n", pid, (WEXITSTATUS(status) == 0) ? "Zakonczony poprawnie" : "Zakonczony z bledem");
      }
    }
  if(signo == SIGINT || signo == SIGTERM)  {
    info_remote_handler(socket, __SERVER_TERMINATE);
    kill(0 ,signo);
  }
}