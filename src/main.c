#include "defines.h"

int main (int argc, char **argv)  {

  int socketDescriptor;
  struct sockaddr_in serverAddress;

  sigset(SIGCHLD, signal_handler);                                                /*czyszczenie pozostalosci po procesach klientow (i nie tylko)*/
  serverAddress = input_parser_local(argc,argv);
  if(serverAddress.sin_port == 0) info_local_handler(__SRV_INVALID_SYNTAX);       /*jezeli uzytkownik nie poda nr'u portu to program program nie rozpocznie nawiazywania polaczenia*/
  socketDescriptor = socket_descriptor_create();
  socket_binder(socketDescriptor,serverAddress);
  socket_listen(socketDescriptor);

  while(wait(0) != -1) continue;                                                 /*zabijanie niedobitkow*/


}