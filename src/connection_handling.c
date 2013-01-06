#include "defines.h"

int socket_descriptor_create(void)  {

  int socketDescriptor = 0;

  if((socketDescriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)  {
    perror("Nie udalo sie utworzyc gniazda");
    exit(1);
    } else  {
    printf("Utworzono gniazdo, desktyptor: %d\n",socketDescriptor);
    return socketDescriptor;
    }


}


int socket_binder(int socketDescriptor, struct sockaddr_in srvAdd)  {

  if(bind(socketDescriptor, (struct sockaddr*) &srvAdd, sizeof(srvAdd)) < 0)  {
    perror("Nie udalo sie dowiązać adresu do gniazda\n");
    close(socketDescriptor);
    exit(1);
    } else  {
    printf("Gniazdo dowiazane prawidlowo\n");
    }


}


void socket_listen(int socketDescriptor)  {

  struct sockaddr_in clientAdd;

  printf("Oczekuje na polaczenie...\n");
  listen(socketDescriptor, __MAX_CONNECT_REQUEST);
  while(1)  {

    int clientPid = 0;
    int clientSock = 0;
    unsigned int clientAddSize;

    clientAddSize = sizeof(clientAdd);
    clientSock = accept(socketDescriptor,(struct sockaddr*) &clientAdd, &clientAddSize);

    if(clientSock < 0)  {
      if(errno == EINTR) continue;
      else  {
        perror("Bląd polaczenia");
        break;
        }
      } else  {
      printf("Zaakceptowano polaczenie. IP klienta: %s:%d\n",inet_ntoa(clientAdd.sin_addr),clientAdd.sin_port);
      clientPid = fork();                                                        /*tworzy osobny watek dla obslugi klienta*/
    }

    if(clientPid < 0)  {
      perror("Nie udalo sie utworzyc procesu dedykowanego");
      close(clientSock);
      break;
      }

    if(clientPid == 0)  {
      signal(SIGTERM, signal_handler);
      signal(SIGINT, signal_handler);
      close(socketDescriptor);
      connection_handler(clientSock);
      close(clientSock);
      printf("Zakonczono polaczenie\n");
      exit(0);
      }
    close(clientSock);
    }


}


void connection_handler(int socket)  {

  int r;
  int status;
  char buffer[__BUFFER_SIZE];
  const char* startLine = ">";
  struct cmdStruct* cmdTemp;
  do  {
    memset(&buffer, 0, sizeof(buffer));                                          /*czyszczenie bufora*/
    status = write(socket, startLine, strlen(startLine));                        /*wyswietlenie znaku zachety u klienta*/
    r = read(socket, buffer, sizeof(buffer));                                    /*oczekujemy na wiadomosc od klienta*/
    if(r > 0)  {
      cmdTemp = splitter(buffer);                                                /*dzielenie wiadomosci na slowa*/
      command_handler(cmdTemp, socket);                                          /*analiza wiadomości i wykonywanie polecen*/
      free(cmdTemp);                                                             /*oproznienie struktury komend*/
    } else if(r == 0)  {
      printf("Klient zakonczyl polaczenie\n");
      } else {
      printf("Blad otrzymanych danych\n");
      }

    } while(r);


}


void command_handler(struct cmdStruct* commandsList, int socket)  {


  if(strncmp(commandsList->words[0], "ls", 2) == 0) command_ls(commandsList, socket);
  else if (strncmp(commandsList->words[0],"get", 3)==0) command_get(commandsList, socket);
  else if (strncmp(commandsList->words[0],"put", 3)==0) command_put(commandsList, socket);
  else if (strncmp(commandsList->words[0],"move", 4)==0) command_move(commandsList, socket);
  else if (strcmp(commandsList->words[0],"replace")==0) command_replace(commandsList, socket);
  else if (strncmp(commandsList->words[0],"rm", 2)==0) command_rm(commandsList, socket);
  else if (strncmp(commandsList->words[0],"quit", 4)==0) command_quit(commandsList, socket);
  else info_remote_handler(socket, __INVALID_COMMAND);


}