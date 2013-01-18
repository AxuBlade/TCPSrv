#ifndef DEFINES_H
#define DEFINES_H

/* Stale do obslugi polaczenia */
#define __MAX_CONNECT_REQUEST 5                                                  /* maksymalna ilosc jednoczesnych zadan dla listen */
#define __BUFFER_SIZE 2048                                                       /* wielkosc buforu odczytu dla komunikacji wewnatrz i na zewnatrz programu */

/* Stale do obslugi komunikatow lokalnych */
#define __SYNTAX_REQUEST 0
#define __SRV_INVALID_SYNTAX 1
#define __STOP_SERVER 2
#define __CLIENT_STOPPED_CONNECTION 3
#define __TRANSFER_ERROR 4
#define __CONNECTION_TERMINATED 5
#define __WAITING_FOR_CONNECTION 6

/* Stale do obslugi komunikatow zdalnych */
#define __TYPE_QUIT 0
#define __TRANSFER_COMPLETE 1
#define __GET_WRONG_SYNTAX 2
#define __PUT_WRONG_SYNTAX 3
#define __REPLACE_WRONG_SYNTAX 4
#define __ERROR_OPENING_FILE 5
#define __COMMAND_EXEC_ERROR 6
#define __INVALID_COMMAND 7
#define __EMPTY_FILE 8
#define __UNEXPECTED_TERMINATION 9


struct cmdStruct  {                                                               /* struktura do przechowywania komend przeslanych przez uzytkownika w postaci poszczegolnych slow */
  char** words;
  int    wordCount;
};

volatile const short unsigned int permissionToRunFlag;

#endif