#include "../defines.h"

void command_replace(struct cmdStruct* commandsList, int socket)  {

  struct cmdStruct* commands1 = (struct cmdStruct*) malloc(sizeof(struct cmdStruct*));
  struct cmdStruct* commands2 = (struct cmdStruct*) malloc(sizeof(struct cmdStruct*));
  char* argvTemp1[2];
  char* argvTemp2[3];
  argvTemp1[0] = "rm";
  argvTemp1[1] = commandsList->words[1];
  argvTemp2[0] = "put";
  argvTemp2[1] = commandsList->words[2];
  argvTemp2[2] = commandsList->words[3];
  commands1->words = argvTemp1;
  commands1->wordCount = 2;
  commands2->wordCount = 3;
  commands2->words = argvTemp2;
  printf("%s %s",commands1->words[0],commands1->words[1]);
  command_rm(commands1, socket);
  command_put(commands2, socket);
}
