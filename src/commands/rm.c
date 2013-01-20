#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../defines.h"
#include "commands.h"
#include "../messages/info_remote_handler.h"
#include "../semaphores/semaphores.h"

void command_rm(struct cmdStruct* commandsList, int socket)  {

  char fifoBuffer[__BUFFER_SIZE];
  int descr[2];
  int stdoutDescr = dup(STDOUT_FILENO);
  int stdinDescr = dup(STDIN_FILENO);
  int stderrDescr = dup(STDERR_FILENO);
  int size = 0;
  int status;
  int cStream = pipe(descr);
  int childPid;
  int semId = semaphore_create(commandsList->words[1], 1);           /* Utworzenie semaforow do zabezpieczenia przed wielokrotną edycją */

  P(semId, 0);

  childPid = fork();

  if(childPid == 0)  {
    dup2(descr[1], 2);                                               /*przekierowanie stderr do FIFO_OUT*/
    dup2(descr[1], 1);                                               /*przekierowanie stdout do FIFO_OUT*/
    close(descr[0]);
    execvp("/bin/rm", commandsList->words);
                                                                     /*jezeli nie uda sie wykonac komendy, zglasza komunikat o bledzie i przywraca wejscia*/
    dup2(stdinDescr, 0);                                              /*przywrocenie poprzednich wejsc*/
    dup2(stdoutDescr, 1);
    dup2(stderrDescr, 2);
    info_remote_handler(socket, __COMMAND_EXEC_ERROR);
  } else  {
      dup2(descr[0], 0);                                             /*przekierowanie stdin na FIFO_IN*/
      close(descr[1]);
      while (1)  {
        memset(fifoBuffer, 0, __BUFFER_SIZE);
        size = read(descr[0], fifoBuffer, sizeof(fifoBuffer));
        status = write(socket, fifoBuffer, size);
        if (size == 0)  {
          close(descr[0]);
          dup2(stdinDescr, 0);                                        /*przywrocenie poprzednich wejsc*/
          dup2(stdoutDescr, 1);
          dup2(stderrDescr, 2);
          break;
        }
      }
      wait(0);
      V(semId, 0);
      if(semaphore_value_lookup(semId, 0)) semaphore_remove(semId);
  }

}