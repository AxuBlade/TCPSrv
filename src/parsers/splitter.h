#ifndef SPLITTER_H
#define SPLITTER_H

struct cmdStruct* splitter(char*);                                             /* dzieli wejscie klienta na slowa w celu pozniejszego przetwarzania */
int splitter_countWords(char*);                                                /* zlicza slowa we wpisanym przez klienta poleceniu */

#endif