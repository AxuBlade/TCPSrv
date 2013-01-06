#include "../defines.h"

void command_move(struct cmdStruct* commandsList, int socket)  {

  char fifoBuffer[__BUFFER_SIZE];
  int descr[2];
  int stdoutDescr = dup(STDOUT_FILENO);
  int stdinDescr = dup(STDIN_FILENO);
  int stderrDescr = dup(STDERR_FILENO);
  int size = 0;
  int status;
  int cStream = pipe(descr);
  int childPid = fork();

  if(childPid == 0)  {
    dup2(descr[1], 2);                                                           /*przekierowanie stderr do FIFO_OUT*/
    dup2(descr[1], 1);                                                           /*przekierowanie stdout do FIFO_OUT*/
    close(descr[0]);
    execvp("/bin/mv", commandsList->words);
                                                                                 /*jezeli nie uda sie wykonac komendy, zglasza komunikat o bledzie i przywraca wejscia*/
    dup2(stdinDescr,0);                                                          /*przywrocenie poprzednich wejsc*/
    dup2(stdoutDescr,1);
    dup2(stderrDescr,2);
    info_remote_handler(socket, __COMMAND_EXEC_ERROR);
    } else  {
    dup2(descr[0], 0);                                                           /*przekierowanie stdin na FIFO_IN*/
    close(descr[1]);
    while(1) {
      bzero(fifoBuffer,__BUFFER_SIZE);
      size = read(descr[0],fifoBuffer,sizeof(fifoBuffer)-1);
      status = write(socket,fifoBuffer,size);
      if (size==0) {
        close(descr[0]);
        dup2(stdinDescr,0);                                                      /*przywrocenie poprzednich wejsc*/
        dup2(stdoutDescr,1);
        dup2(stderrDescr,2);
        break;
        }
      }
    wait(0);
    }


}