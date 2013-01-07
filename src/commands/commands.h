#ifndef COMMANDS_H
#define COMMANDS_H

void command_ls(struct cmdStruct*, int);         /* wyswietla na ekranie drzewo katalogu. skladnia taka jak dla /bin/ls */
void command_get(struct cmdStruct*, int);        /* wysyla plik z serwera */
void command_put(struct cmdStruct*, int);        /* wysyla plik na serwer */
void command_move(struct cmdStruct*, int);       /* zmienia nazwe/przenosi plik/katalog. skladnia jak dla /bin/mv */
void command_replace(struct cmdStruct*, int);    /* zastepuje plik na serwerze, plikiem przeslamym przez klienta */
void command_rm(struct cmdStruct*, int);         /* usuwa plik/katalog. skladnia jak dla /bin/rm */
void command_quit(struct cmdStruct*, int);       /* obsluga oczekiwanego zakonczenia polaczenia */

#endif