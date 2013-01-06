#include <arpa/inet.h>
#include <errno.h>
#include <getopt.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define __MAX_CONNECT_REQUEST 5                                                  /*maksymalna ilosc jednoczesnych zadan dla listen*/
#define __BUFFER_SIZE 2048                                                       /*wielkosc buforu odczytu dla komunikacji wewnatrz i na zewnatrz programu*/



#define __TYPE_QUIT 0
#define __NOT_ENOUGH_ARGUMENTS 1
#define __TRANSFER_COMPLETE 2
#define __ERROR_OPENING_FILE 3
#define __COMMAND_EXEC_ERROR 4
#define __INVALID_COMMAND 5
#define __EMPTY_FILE 6

struct cmdStruct {                                                               /*struktura do przechowywania komend przeslanych przez uzytkownika w postaci poszczegolnych slow*/
  char** words;
  int    wordCount;
};

int socket_descriptor_create (void);                                             /*tworzy desktyptor gniazda*/
struct sockaddr_in pars_input (int , char**);                                    /*parsuje wejscie, zwraca strukture z portem i adresem serwera*/
struct cmdStruct* splitter(char*);                                               /*dzieli wejscie klienta na slowa w celu pozniejszego przetwarzania*/
void connection_handler(int);                                                    /*obsluguje polaczenie*/
void command_handler(struct cmdStruct*, int);                                    /*obsluguje polecenia klienta*/
void command_ls(struct cmdStruct*, int);                                         /*wyswietla na ekranie drzewo katalogu. skladnia taka jak dla /bin/ls */
void command_get(struct cmdStruct*, int);
void command_put(struct cmdStruct*, int);
void command_move(struct cmdStruct*, int);                                       /*zmienia nazwe/przenosi plik/katalog. skladnia jak dla /bin/mv */
void command_replace(struct cmdStruct*, int);
void command_rm(struct cmdStruct*, int);                                         /*usuwa plik/katalog. skladnia jak dla /bin/rm*/
void command_quit(struct cmdStruct*, int);                                       /*obsluga oczekiwanego zakonczenia polaczenia*/
void signal_handler(int);                                                        /*obsluga SIGINT,SIGTERM i SIGCHLD*/
void info_transmission_handler(int, int);                                        /*obsluga komunikatow dla klienta*/
void display_usage (void);                                                       /*wyswietla komunikat o prawidlowej skladni*/