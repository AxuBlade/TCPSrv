#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../defines.h"
#include "commands.h"
#include "../messages/info_remote_handler.h"

void command_replace(struct cmdStruct* commandsList, int socket) {

  FILE* fileStream;
  char writeBuffer[__BUFFER_SIZE];
  int recvSize = 0;
  int writeSize = 0;
  int textModeCheck = !strncmp(commandsList->words[3],"-t",2) || !strncmp(commandsList->words[3],"--text",8);
  int binaryModeCheck = !strncmp(commandsList->words[3],"-b",2) || !strncmp(commandsList->words[3],"--binary",8);
  char* writeMode;
  char* writeModeText = "wt";
  char* writeModeBinary = "wr";
  struct stat fileStat;

  signal(SIGINT, SIG_IGN);
  signal(SIGTERM, SIG_IGN);
  if(commandsList->wordCount == 4 && (textModeCheck || binaryModeCheck))  {
    if(textModeCheck) writeMode = writeModeText;
    else if(binaryModeCheck) writeMode = writeModeBinary;
    if((fileStream = fopen(commandsList->words[1],writeMode)) == NULL)  {
      info_remote_handler(socket, __ERROR_OPENING_FILE);
      shutdown(socket, 0);
      close(socket);
      exit(1);
    } else  {
        while((recvSize = recv(socket, writeBuffer, __BUFFER_SIZE, 0)) > 0) {
          writeSize = fwrite(writeBuffer, sizeof(char), recvSize, fileStream);
        }
        fclose(fileStream);
        stat(commandsList->words[1], &fileStat);
        if(!fileStat.st_size)  {
          printf("Odebrano pusty plik plik %s -> usuwanie\n", commandsList->words[2], (signed int) fileStat.st_size);
          info_remote_handler(socket,__EMPTY_FILE);
          remove(commandsList->words[1]);
        } else printf("Odebrano plik %s o rozmiarze %d\n", commandsList->words[2], (signed int) fileStat.st_size);
        shutdown(socket,0);
        close(socket);
        exit(0);
    }
  } else info_remote_handler(socket,__PUT_WRONG_SYNTAX);


}