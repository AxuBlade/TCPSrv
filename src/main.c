#include <netinet/in.h>
#include <signal.h>
#include <sys/socket.h>
#include <wait.h>
#include <stdlib.h>

#include "defines.h"
#include "connection_handling.h"
#include "messages/info_local_handler.h"
#include "parsers/input_parser.h"
#include "signals/signals.h"

int main(int argc, char **argv)  {

  int socketDescriptor;
  struct sockaddr_in serverAddress;
  volatile unsigned short int* setFlag = (volatile unsigned short int*) &permissionToRunFlag;

  sigset(SIGCHLD, signal_handler);                                             /* SEKCJA OBSLUGI SYGNALOW */
  sigset(SIGINT, signal_handler);
  sigset(SIGTERM, signal_handler);

  *setFlag = 1;
  clear_screen();
  serverAddress = input_parser(argc,argv);                                     /* SEKCJA PARSUJACA PARAMETRY URUCHOMIENIA */
  if (serverAddress.sin_port == 0) info_local_handler(__SRV_INVALID_SYNTAX);   /* jezeli uzytkownik nie poda nr'u portu, program nie rozpocznie nawiazywania polaczenia */
  else {
    socketDescriptor = socket_descriptor_create();                             /* SEKCJA TWORZENIA POLACZENIA */
    socket_binder(socketDescriptor, serverAddress);
    socket_listen(socketDescriptor);
  }

  while (wait(0) != -1) continue;                                              /* ewentualne zakonczenie procesow potomnych */
  exit(0);

}