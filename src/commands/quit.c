#include <stdlib.h>
#include <unistd.h>
#include "../defines.h"
#include "commands.h"
#include "../messages/info_remote_handler.h"

void command_quit(struct cmdStruct* cmdStruct, int socket)  {

  info_remote_handler(socket, __TYPE_QUIT);
  close(socket);
  free(cmdStruct);
  while(wait(0) != -1) continue;
  exit(0);


}