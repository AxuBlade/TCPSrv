#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "defines.h"
#include "connection_handling.h"
#include "commands/commands.h"
#include "messages/info_remote_handler.h"
#include "messages/info_local_handler.h"
#include "parsers/splitter.h"
#include "signals/signals.h"

int socket_descriptor_create(void)  {

  int socketDescriptor = 0;

  if ((socketDescriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)  {
    perror("!! Nie udalo sie utworzyc gniazda");
    exit(1);
  } else  {
      fcntl(socketDescriptor, F_SETFL, O_NONBLOCK);
      return socketDescriptor;
  }

}


int socket_binder(int socketDescriptor, struct sockaddr_in srvAdd)  {

  if (bind(socketDescriptor, (struct sockaddr*) &srvAdd, sizeof(srvAdd)) < 0)  {
    perror("!! Nie udalo sie dowiązać adresu do gniazda\n");
    close(socketDescriptor);
    exit(1);
  }

}


void socket_listen(int socketDescriptor)  {

  struct sockaddr_in clientAdd;

  info_local_handler(__WAITING_FOR_CONNECTION);
  listen(socketDescriptor, __MAX_CONNECT_REQUEST);

  do  {

    int clientPid = 0;
    int clientSock = 0;
    unsigned int clientAddSize;

    clientAddSize = sizeof(clientAdd);
    clientSock = accept4(socketDescriptor, (struct sockaddr*) &clientAdd, &clientAddSize, 0&~SOCK_NONBLOCK);
    if (clientSock < 0)  {
      if (errno == EINTR || errno == EAGAIN  || errno == EWOULDBLOCK) continue;
      else  {
        perror("!! Bląd polaczenia");
        break;
      }
    } else  {
        clientPid = fork();                                          /*tworzy osobny watek dla obslugi klienta*/
    }
    if (clientPid < 0)  {
      perror("!! Nie udalo sie utworzyc procesu dedykowanego");
      close(clientSock);
      break;
    }
    if (clientPid == 0)  {
      close(socketDescriptor);
      __connection_handler(clientSock);
      close(clientSock);
      info_local_handler(__CONNECTION_TERMINATED);
      exit(0);
    }
    else printf(">> Zaakceptowano polaczenie. IP klienta: %s:%d\n>>>> PID procesu do obsługi klienta: %d\n", inet_ntoa(clientAdd.sin_addr), clientAdd.sin_port, clientPid);
    close(clientSock);
  } while (permissionToRunFlag);

  close(socketDescriptor);
  info_local_handler(__STOP_SERVER);

}


void __connection_handler(int socket)  {

  int readSize = 0;
  int status = 0;
  char buffer[__BUFFER_SIZE];
  const char* startLine = ">";
  struct cmdStruct* cmdTemp;

  do  {
    memset(&buffer, 0, sizeof(buffer));                              /*czyszczenie bufora*/
    status = write(socket, startLine, strlen(startLine));            /*wyswietlenie znaku zachety u klienta*/
    readSize = read(socket, buffer, sizeof(buffer));                 /*oczekujemy na wiadomosc od klienta*/

    if (readSize > 0)  {
      cmdTemp = splitter(buffer);                                    /*dzielenie wiadomosci na slowa*/
      __command_handler(cmdTemp, socket);                            /*analiza wiadomości i wykonywanie polecen*/
      free(cmdTemp);                                                 /*oproznienie struktury komend*/
    } else if (readSize == 0)  {
        info_local_handler(__CLIENT_STOPPED_CONNECTION);
        break;
    } else if (permissionToRunFlag) {
        info_local_handler(__TRANSFER_ERROR);
    }
  } while (readSize && permissionToRunFlag);
  if (!permissionToRunFlag) info_remote_handler(socket, __UNEXPECTED_TERMINATION);

}


void __command_handler(struct cmdStruct* commandsList, int socket)  {

  if (permissionToRunFlag) {
    if (strncmp(commandsList->words[0], "ls", 2) == 0) command_ls(commandsList, socket);
    else if (strncmp(commandsList->words[0], "rm", 2) == 0) command_rm(commandsList, socket);
    else if (strncmp(commandsList->words[0], "get", 3) == 0) command_get(commandsList, socket);
    else if (strncmp(commandsList->words[0], "put", 3) == 0) command_put(commandsList, socket);
    else if (strncmp(commandsList->words[0], "move", 4) == 0) command_move(commandsList, socket);
    else if (strncmp(commandsList->words[0], "quit", 4) == 0) command_quit(commandsList, socket);
    else if (strncmp(commandsList->words[0], "replace", 7) == 0) command_replace(commandsList, socket);
    else info_remote_handler(socket, __INVALID_COMMAND);
  }

}