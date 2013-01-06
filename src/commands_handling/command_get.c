#include "../defines.h"

void command_get(struct cmdStruct* commandsList, int socket)  {

  FILE* fileStream;
  char readBuffer[__BUFFER_SIZE];
  int readSize = 0;
  int textModeCheck = !strncmp(commandsList->words[3],"-t",2) || !strncmp(commandsList->words[3],"--text",8);
  int binaryModeCheck = !strncmp(commandsList->words[3],"-b",2) || !strncmp(commandsList->words[3],"--binary",8);
  char* readModeBinary = "rb";
  char* readModeText = "rt";
  char* readMode;
  struct stat fileStat;

  signal(SIGINT, SIG_IGN);
  signal(SIGTERM, SIG_IGN);
  if(commandsList->wordCount == 4 && (textModeCheck || binaryModeCheck))  {
    if(textModeCheck) readMode = readModeText;
    else if(binaryModeCheck) readMode = readModeBinary;
    if((fileStream = fopen(commandsList->words[1],readMode)) == NULL)  {
      info_remote_handler(socket, __ERROR_OPENING_FILE);
      shutdown(socket, 1);
      } else  {
      while((readSize = fread(readBuffer, sizeof(char), __BUFFER_SIZE, fileStream)) > 0)  {
        send(socket, readBuffer, readSize, 0);
        }
      fclose(fileStream);
      stat(commandsList->words[1], &fileStat);
      printf("Wyslano %d bajtow\n", (signed int)fileStat.st_size);
      fflush(stdout);
      shutdown(socket, 1);
      }
    } else info_remote_handler(socket,__GET_WRONG_SYNTAX);


}