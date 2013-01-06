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

/* Stale do obslugi polaczenia */
#define __MAX_CONNECT_REQUEST 5                                                  /* maksymalna ilosc jednoczesnych zadan dla listen */
#define __BUFFER_SIZE 2048                                                       /* wielkosc buforu odczytu dla komunikacji wewnatrz i na zewnatrz programu */

/* Stale do obslugi komunikatow lokalnych */
#define __SYNTAX_REQUEST 0
#define __SRV_INVALID_SYNTAX 1

/* Stale do obslugi komunikatow zdalnych */
#define __TYPE_QUIT 0
#define __TRANSFER_COMPLETE 1
#define __GET_WRONG_SYNTAX 2
#define __PUT_WRONG_SYNTAX 3
#define __ERROR_OPENING_FILE 4
#define __COMMAND_EXEC_ERROR 5
#define __INVALID_COMMAND 6
#define __EMPTY_FILE 7
#define __SERVER_TERMINATE 8


struct cmdStruct  {                                                               /* struktura do przechowywania komend przeslanych przez uzytkownika w postaci poszczegolnych slow */
  char** words;
  int    wordCount;
};

/* connection_handling.c */
int socket_descriptor_create (void);                                           /* tworzy desktyptor gniazda */
void connection_handler(int);                                                  /* obsluguje polaczenie */
void command_handler(struct cmdStruct*, int);                                  /* obsluguje polecenia klienta */
int socket_binder(int, struct sockaddr_in);                                    /* kojarzenie gniazd */
void socket_listen(int);                                                       /* obsluga nasluchiwania */
struct sockaddr_in input_parser_local (int, char**);                           /* parsuje wejscie, zwraca strukture z portem i adresem serwera */
struct cmdStruct* splitter(char*);                                             /* dzieli wejscie klienta na slowa w celu pozniejszego przetwarzania */

/* commands_handling/ */
void command_ls(struct cmdStruct*, int);                                       /* wyswietla na ekranie drzewo katalogu. skladnia taka jak dla /bin/ls */
void command_get(struct cmdStruct*, int);                                      /* wysyla plik z serwera */
void command_put(struct cmdStruct*, int);                                      /* wysyla plik na serwer */
void command_move(struct cmdStruct*, int);                                     /* zmienia nazwe/przenosi plik/katalog. skladnia jak dla /bin/mv */
void command_replace(struct cmdStruct*, int);                                  /* zastepuje plik na serwerze, plikiem przeslamym przez klienta */
void command_rm(struct cmdStruct*, int);                                       /* usuwa plik/katalog. skladnia jak dla /bin/rm */
void command_quit(struct cmdStruct*, int);                                     /* obsluga oczekiwanego zakonczenia polaczenia */

/* signals_handling/signals.c */
void signal_handler(int);                                                      /* obsluga SIGINT,SIGTERM i SIGCHLD */

/* messages_handling/info_remote_handler.c */
void info_remote_handler(int, int);                                            /* obsluga komunikatow zdalnych */

/* messages_handling/info_local_handler */
void info_local_handler(int);                                                  /* obsluga komunikatow lokalnych */