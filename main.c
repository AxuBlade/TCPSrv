#include "header.h"


struct sockaddr_in pars_input(int argc_s, char **argv_s) {

  int opt;
  struct sockaddr_in parsedArgs;
  static const char *optString = "i:p:";                                         /*rozpoznawalne krotkie opcje dla parsera*/
  static const struct option longOpts[] = {
    {"interface", required_argument, NULL, 'i'},                                 /*tablica opcji z pelnymi nazwami opcji*/
    {"port", required_argument, NULL, 'p'}                                       /*oraz ich nazwami skrotowymi*/
    };


  memset(&parsedArgs, 0, sizeof(struct sockaddr_in) );

  parsedArgs.sin_addr.s_addr = htonl(INADDR_ANY);                                /*domyslnie: wyszstkie interfejsy o ile uztkownik nie poda na wejsciu adresu*/

  while((opt = getopt_long(argc_s, argv_s, optString, longOpts, NULL )) != -1)  {
    switch(opt)  {
      case 'p':
        parsedArgs.sin_port = htons((short) atoi(optarg));
        break;

      case 'i':
        parsedArgs.sin_addr.s_addr = inet_addr(optarg);
        break;

      default:                                                                   /*opcja tylko dla celow zgodnosci ze standardem. Nie ma prawa wystąpic*/
        break;
    }
  }

  parsedArgs.sin_family = AF_INET;

  return parsedArgs;


}

/****************************************************/

int socket_descriptor_create(void)  {

  int socketDescriptor = 0;

  if((socketDescriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)  {
    perror("nie udalo sie utworzyc gniazda");
    exit(1);
    } else  {
    printf("utworzono gniazdo, desktyptor: %d\n",socketDescriptor);
    return socketDescriptor;
    }


}

/****************************************************/

int socket_binder(int socketDescriptor, struct sockaddr_in srvAdd)  {

  if(bind(socketDescriptor, (struct sockaddr*) &srvAdd, sizeof(srvAdd)) < 0)  {
    perror("Nie udalo sie dowiązać adresu do gniazda\n");
    close(socketDescriptor);
    exit(1);
    } else  {
    printf("gniazdo dowiazane prawidlowo\n");
    }


}

/****************************************************/

void socket_listen(int socketDescriptor)  {

  int endIndicator = 0;
  struct sockaddr_in clientAdd;

  printf("oczekuje na polaczenie...\n");
  listen(socketDescriptor, __MAX_CONNECT_REQUEST);

  while(!endIndicator)  {

    int clientPid = 0;
    int clientSock = 0;
    unsigned int clientAddSize;

    clientAddSize = sizeof(clientAdd);
    clientSock = accept(socketDescriptor,(struct sockaddr*) &clientAdd, &clientAddSize);

    if(clientSock < 0)  {
      if(errno == EINTR) continue;
      else  {
        perror("bląd polaczenia");
        endIndicator = 1;
        }
      } else  {
      printf("zaakceptowano polaczenie. IP klienta: %s:%d\n",inet_ntoa(clientAdd.sin_addr),clientAdd.sin_port);
      clientPid = fork();                                                        /*tworzy osobny watek dla obslugi klienta*/
    }

    if(clientPid < 0)  {
      perror("nie udalo sie utworzyc procesu dedykowanego");
      close(clientSock);
      endIndicator = 1;
      }

    if(clientPid == 0)  {
      close(socketDescriptor);
      connection_handler(clientSock);
      close(clientSock);
      printf("zakonczono polaczenie\n");
      exit(0);
      }
    close(clientSock);
    }


}

/****************************************************/

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
      printf("klient zakonczyl polaczenie\n");
      } else {
      printf("blad otrzymanych danych\n");
      }

    } while(r);


}

/****************************************************/

int splitter_countWords(char* buffer)  {

  int i;
  int wordCount = 0;

  for(i = 0; i < (strlen(buffer)); ++i)  {
    if((int)buffer[i] == 32) wordCount++;
    }
  return wordCount + 1;


}

/****************************************************/

struct cmdStruct* splitter(char* buffer)  {

  int i;
  int wordSize = 0;
  int vTabSize = splitter_countWords(buffer);
  char spaces[] = {' ', '\n', '\0'};                                             /*tablica bialych znaków, mozliwych do wystapienia (spacja i nowa linia)*/
  char** temp = (char**) malloc((vTabSize + 1) * sizeof(char*));
  struct cmdStruct* tempStruct;

  tempStruct = (struct cmdStruct*) malloc(sizeof(struct cmdStruct));             /*inicjalizacja struktury*/
  for(i = 0; i < vTabSize; ++i)  {
    wordSize = strcspn(buffer, spaces);
    temp[i] = (char*) malloc((wordSize + 1) * sizeof(char));
    memset(temp[i], 0, sizeof(temp[i]));
    strncpy(temp[i], buffer, wordSize);
    buffer = buffer + wordSize + 1;
    }

  temp[vTabSize] = NULL;                                                           /*ostatni element tablicy **words musi miec wartosc NULL dla zgodnosci z execvp*/

  tempStruct->wordCount = vTabSize;
  tempStruct->words = temp;

  return tempStruct;


}

/****************************************************/

void command_handler(struct cmdStruct* commandsList, int socket)  {

  char* errorString = "Nieprawidlowe polecenie!\n";

  if(strcmp(commandsList->words[0], "ls") == 0) command_ls(commandsList, socket);
  else if (strcmp(commandsList->words[0],"get")==0) command_get(commandsList,socket);
  else if (strcmp(commandsList->words[0],"put")==0) command_put(commandsList,socket);
  else if (strcmp(commandsList->words[0],"move")==0) command_move(commandsList,socket);
  /*else if (strcmp(commandsList->words[0],"replace")==0) command_replace(cmdTemp,socket);*/
  else if (strcmp(commandsList->words[0],"rm")==0) command_rm(commandsList,socket);
  else if (strcmp(commandsList->words[0],"quit")==0) command_quit(commandsList, socket);
  else {
    write(socket, errorString, strlen(errorString));
    }


}

/****************************************************/

void command_ls(struct cmdStruct* commandsList, int socket)  {

  char fifoBuffer[__BUFFER_SIZE];
  char* errorMsg = "Nie udalo sie wykonac polecenia\n";
  int descr[2];
  int stdoutDescr = dup(STDOUT_FILENO);
  int stdinDescr = dup(STDIN_FILENO);
  int stderrDescr = dup(STDERR_FILENO);
  int size = 0;
  int status;
  int cStream = pipe(descr);
  int childPid = fork();

  if(childPid == 0)  {
    dup2(descr[1], 2);                                                           /*przekierowanie stderr do FIFO_OUT*/
    dup2(descr[1], 1);                                                           /*przekierowanie stdout do FIFO_OUT*/
    close(descr[0]);
    execvp("/bin/ls", commandsList->words);
                                                                                 /*jezeli nie uda sie wykonac komendy, zglasza komunikat o bledzie i przywraca wejscia*/
    dup2(stdinDescr,0);                                                          /*przywrocenie poprzednich wejsc*/
    dup2(stdoutDescr,1);
    dup2(stderrDescr,2);
    write(socket,errorMsg,strlen(errorMsg));
    } else  {
    dup2(descr[0], 0);                                                           /*przekierowanie stdin na FIFO_IN*/
    close(descr[1]);
    while(1) {
      bzero(fifoBuffer,__BUFFER_SIZE);
      size = read(descr[0],fifoBuffer,sizeof(fifoBuffer)-1);
      status = write(socket,fifoBuffer,size);
      if (size==0) {
        close(descr[0]);
        dup2(stdinDescr,0);                                                      /*przywrocenie poprzednich wejsc*/
        dup2(stdoutDescr,1);
        dup2(stderrDescr,2);
        break;
        }
      }
    wait(0);
    }


}

/****************************************************/

void command_get(struct cmdStruct* commandsList, int socket)  {

  FILE* fileStream;
  char readBuffer[__BUFFER_SIZE];
  int readSize = 0;
  char* errorMsg = "Nie udalo sie otworzyc pliku\n";

  if(!strncmp(commandsList->words[2],"-t",2) || !strncmp(commandsList->words[2],"--text",6))  {
    if((fileStream = fopen(commandsList->words[1],"rt")) == NULL)  {
      write(socket,errorMsg,strlen(errorMsg));
      } else  {
      while((readSize = fread(readBuffer, sizeof(char), __BUFFER_SIZE, fileStream)) > 0)  {
        send(socket, readBuffer, readSize, 0);
        }
      fclose(fileStream);
      }
    } else if(!strncmp(commandsList->words[2],"-b",2) || !strncmp(commandsList->words[2],"--binary",8))  {
    if((fileStream = fopen(commandsList->words[1],"rb")) == NULL)  {
      write(socket,errorMsg,strlen(errorMsg));
      }
  else  {

    }
  }


}

/****************************************************/

void command_put(struct cmdStruct* commandsList, int socket)  {

  FILE* fileStream;
  char writeBuffer[__BUFFER_SIZE];
  int recvSize = 0;
  int writeSize = 0;
  char* errorMsg1 = "Nie udalo sie utworzyc pliku\n";
  char* errorMsg2 = "Blad transmisji\n";

  if(!strncmp(commandsList->words[2],"-t",2) || !strncmp(commandsList->words[2],"--text",6))  {
    if((fileStream = fopen(commandsList->words[1],"wt")) == NULL)  {
      write(socket,errorMsg1,strlen(errorMsg1));
      }
    else  {
      while((recvSize = recv(socket, writeBuffer, __BUFFER_SIZE, 0)) > 0) {
        writeSize = fwrite(writeBuffer, sizeof(char), recvSize, fileStream);
        if(recvSize != writeSize) write(socket, errorMsg2, strlen(errorMsg2));
        remove(commandsList->words[2]);
        break;
      }
      fclose(fileStream);
      }
    }

  else if(!strncmp(commandsList->words[2],"-b",2) || !strncmp(commandsList->words[2],"--binary",8))  {
    if((fileStream = fopen(commandsList->words[1],"rb")) == NULL)  {
      write(socket,errorMsg1,strlen(errorMsg1));
      }
    else  {


    }
  }


}

/****************************************************/

void command_move(struct cmdStruct* commandsList, int socket)  {

  char fifoBuffer[__BUFFER_SIZE];
  char* errorMsg = "Nie udalo sie wykonac polecenia\n";
  int descr[2];
  int stdoutDescr = dup(STDOUT_FILENO);
  int stdinDescr = dup(STDIN_FILENO);
  int stderrDescr = dup(STDERR_FILENO);
  int size = 0;
  int status;
  int cStream = pipe(descr);
  int childPid = fork();

  if(childPid == 0)  {
    dup2(descr[1], 2);                                                           /*przekierowanie stderr do FIFO_OUT*/
    dup2(descr[1], 1);                                                           /*przekierowanie stdout do FIFO_OUT*/
    close(descr[0]);
    execvp("/bin/mv", commandsList->words);
                                                                                 /*jezeli nie uda sie wykonac komendy, zglasza komunikat o bledzie i przywraca wejscia*/
    dup2(stdinDescr,0);                                                          /*przywrocenie poprzednich wejsc*/
    dup2(stdoutDescr,1);
    dup2(stderrDescr,2);
    write(socket,errorMsg,strlen(errorMsg));
    } else  {
    dup2(descr[0], 0);                                                           /*przekierowanie stdin na FIFO_IN*/
    close(descr[1]);
    while(1) {
      bzero(fifoBuffer,__BUFFER_SIZE);
      size = read(descr[0],fifoBuffer,sizeof(fifoBuffer)-1);
      status = write(socket,fifoBuffer,size);
      if (size==0) {
        close(descr[0]);
        dup2(stdinDescr,0);                                                      /*przywrocenie poprzednich wejsc*/
        dup2(stdoutDescr,1);
        dup2(stderrDescr,2);
        break;
        }
      }
    wait(0);
    }


}

/****************************************************/

void command_rm(struct cmdStruct* commandsList, int socket)  {

  char fifoBuffer[__BUFFER_SIZE];
  char* errorMsg = "Nie udalo sie wykonac polecenia\n";
  int descr[2];
  int stdoutDescr = dup(STDOUT_FILENO);
  int stdinDescr = dup(STDIN_FILENO);
  int stderrDescr = dup(STDERR_FILENO);
  int size = 0;
  int status;
  int cStream = pipe(descr);
  int childPid = fork();

  if(childPid == 0)  {
    dup2(descr[1], 2);                                                           /*przekierowanie stderr do FIFO_OUT*/
    dup2(descr[1], 1);                                                           /*przekierowanie stdout do FIFO_OUT*/
    close(descr[0]);
    execvp("/bin/rm", commandsList->words);
                                                                                 /*jezeli nie uda sie wykonac komendy, zglasza komunikat o bledzie i przywraca wejscia*/
    dup2(stdinDescr,0);                                                          /*przywrocenie poprzednich wejsc*/
    dup2(stdoutDescr,1);
    dup2(stderrDescr,2);
    write(socket,errorMsg,strlen(errorMsg));
    } else  {
    dup2(descr[0], 0);                                                           /*przekierowanie stdin na FIFO_IN*/
    close(descr[1]);
    while(1) {
      bzero(fifoBuffer,__BUFFER_SIZE);
      size = read(descr[0],fifoBuffer,sizeof(fifoBuffer)-1);
      status = write(socket,fifoBuffer,size);
      if (size==0) {
        close(descr[0]);
        dup2(stdinDescr,0);                                                      /*przywrocenie poprzednich wejsc*/
        dup2(stdoutDescr,1);
        dup2(stderrDescr,2);
        break;
        }
      }
    wait(0);
    }


}

/****************************************************/

void command_quit(struct cmdStruct* cmdStruct, int socket)  {

  char* endMessage = "Zakonczono polaczenie z serwerem\n";
  write(socket,endMessage,strlen(endMessage));
  close(socket);
  free(cmdStruct);
  while(wait(0) != -1) continue;
  exit(0);



}

/****************************************************/


void signal_reaper(int signo)  {

  pid_t pid;
  int status;

  while((pid=waitpid(-1,&status,WNOHANG)) > 0)  {
    printf("proces PID = %d, STATUS = %s\n", pid, (WEXITSTATUS(status) == 0) ? "Zakonczony poprawnie" : "Zakonczony z bledem");
    }


}

/****************************************************/

int main (int argc, char **argv)  {

  int socketDescriptor;
  struct sockaddr_in serverAddress;

  sigset(SIGCHLD,signal_reaper);                                                 /*czyszczenie pozostalosci po procesach klientow (i nie tylko)*/

  serverAddress = pars_input(argc,argv);
  if(serverAddress.sin_port == 0) display_usage();                               /*jezeli uzytkownik nie poda nr'u portu to program pokaze monit z poprawna skladnia (helpscreen)*/
  socketDescriptor = socket_descriptor_create();
  socket_binder(socketDescriptor,serverAddress);
  socket_listen(socketDescriptor);

  while(wait(0) != -1) continue;                                                 /*zabijanie niedobitkow*/


}