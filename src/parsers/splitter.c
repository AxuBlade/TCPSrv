#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "splitter.h"
#include "../defines.h"


int splitter_countWords(char* buffer)  {

  int i;
  int wordCount = 1;

  for (i = 0; i < (strlen(buffer)); ++i)  {
    if ((int)buffer[i] == 32) wordCount++;
  }
  return wordCount;


}


struct cmdStruct* splitter(char* buffer)  {

  int i;
  int wordSize = 0;
  int vTabSize = splitter_countWords(buffer);
  char spaces[] = {' ', '\n', '\0'};                                           /*tablica bialych znaków, mozliwych do wystapienia (spacja i nowa linia)*/
  char** temp = (char**) malloc((vTabSize + 1) * sizeof(char*));
  struct cmdStruct* tempStruct;

  tempStruct = (struct cmdStruct*) malloc(sizeof(struct cmdStruct));           /*inicjalizacja struktury*/
  for (i = 0; i < vTabSize; ++i)  {
    wordSize = strcspn(buffer, spaces);
    temp[i] = (char*) malloc((wordSize + 1) * sizeof(char));
    memset(temp[i], 0, sizeof(temp[i]));
    strncpy(temp[i], buffer, wordSize);
    buffer = buffer + wordSize + 1;
  }

  temp[vTabSize] = NULL;                                                       /*ostatni element tablicy **words musi miec wartosc NULL dla zgodnosci z execvp*/
  tempStruct->wordCount = vTabSize;
  tempStruct->words = temp;

  return tempStruct;

}