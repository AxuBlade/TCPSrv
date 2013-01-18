#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include "../defines.h"
#include "commands.h"
#include "../messages/info_remote_handler.h"
#include "../semaphores/semaphores.h"

void command_get(struct cmdStruct* commandsList, int socket)  {

  FILE* fileStream;
  char readBuffer[__BUFFER_SIZE];
  int readSize = 0;
  int sentSize = 0;
  char* readModeBinary = "rb";
  char* readModeText = "rt";
  char* readMode;
  struct stat fileStat;

  signal(SIGINT, SIG_IGN);
  signal(SIGTERM, SIG_IGN);
  
  if (commandsList->wordCount == 4 )  {
    int textModeCheck = !strncmp(commandsList->words[3], "-t", 2) || !strncmp(commandsList->words[3], "--text", 6);
    int binaryModeCheck = !strncmp(commandsList->words[3], "-b", 2) || !strncmp(commandsList->words[3], "--binary", 8);
    if (textModeCheck || binaryModeCheck)  {
      if (textModeCheck) readMode = readModeText;
      else if (binaryModeCheck) readMode = readModeBinary;
      if ((fileStream = fopen(commandsList->words[1], readMode)) == NULL)  {
        info_remote_handler(socket, __ERROR_OPENING_FILE);
        shutdown(socket, 1);
      } else  {
          int semId = semaphore_create(commandsList->words[2], 1);
          P(semId, 0);
          while ((readSize = fread(readBuffer, sizeof(char), __BUFFER_SIZE, fileStream)) > 0)  {
            sentSize += send(socket, readBuffer, readSize, 0);
          }
          fclose(fileStream);
          stat(commandsList->words[1], &fileStat);
          printf("PLIK %s: Rozmiar: %dB Wyslano %dB\n", commandsList->words[1], (signed int)fileStat.st_size, sentSize);
          fflush(stdout);
          shutdown(socket, 1);
          V(semId, 0);

          if (semaphore_value_lookup(semId, 0)) semaphore_remove(semId);
          exit(0);
      }
    } else info_remote_handler(socket, __GET_WRONG_SYNTAX);
  } else info_remote_handler(socket, __GET_WRONG_SYNTAX);

}