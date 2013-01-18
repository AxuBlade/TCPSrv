#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../defines.h"
#include "commands.h"
#include "../messages/info_remote_handler.h"

void command_quit(struct cmdStruct* cmdStruct, int socket)  {

  info_remote_handler(socket, __TYPE_QUIT);

}