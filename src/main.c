#include <netinet/in.h>
#include <signal.h>
#include <sys/socket.h>
#include <wait.h>
#include "defines.h"
#include "connection_handling.h"
#include "messages/info_local_handler.h"
#include "parsers/input_parser.h"
#include "signals/signals.h"


int main (int argc, char **argv)  {

  int socketDescriptor;
  struct sockaddr_in serverAddress;
  volatile unsigned short int* setFlag = (volatile unsigned short int*) &permissionToRunFlag;

  sigset(SIGCHLD, signal_handler);                                             /*czyszczenie pozostalosci po procesach klientow (i nie tylko)*/
  sigset(SIGINT, signal_handler);
  sigset(SIGTERM, signal_handler);

  *setFlag = 1;

  serverAddress = input_parser(argc,argv);
  if(serverAddress.sin_port == 0) info_local_handler(__SRV_INVALID_SYNTAX);    /*jezeli uzytkownik nie poda nr'u portu to program program nie rozpocznie nawiazywania polaczenia*/
  socketDescriptor = socket_descriptor_create();
  socket_binder(socketDescriptor,serverAddress);
  socket_listen(socketDescriptor);


}