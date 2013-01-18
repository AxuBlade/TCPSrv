#include <string.h>
#include <unistd.h>
#include "info_remote_handler.h"
#include "../defines.h"


void info_remote_handler(int socket, int iType)  {

  char* quitMsg = "Serwer: Zakonczono polaczenie z serwerem\n";
  char* getSyntax = "\nSkladnia polecenia get:\n\nget  [ZDALNA_NAZWA_PLIKU_DO_POBRANIA] [LOKALNA_SCIEZKA_PLIKU][FLAGA_TRYBU]\nDostepne flagi:\n-b --binary    Binarny tryb transferu\n-t --text      Tekstowy tryb transferu\n";
  char* putSyntax = "\nSkladnia polecenia put:\n\nput  [LOKALNA_SCIEZKA_PLIKU_DO_WYSLANIA] [ZDALNA_NAZWA_PLIKU] [FLAGA_TRYBU]\nDostepne flagi:\n-b --binary    Binarny tryb transferu\n-t --text      Tekstowy tryb transferu\n";
  char* replaceSyntax = "\nSkladnia polecenia replace:\n\nreplace  [ZDALNA_SCIEZKA_PLIKU_DO_PODMIANY] [LOKALNA_NAZWA_PLIKU] [FLAGA_TRYBU]\nDostepne flagi:\n-b --binary    Binarny tryb transferu\n-t --text      Tekstowy tryb transferu\n";
  char* transferComplete = "Serwer: Plik zapisano pomyslnie\n";
  char* openingFileError = "Serwer: Nie udalo sie otworzyc pliku\n";
  char* commandExecutionError = "Serwer: Nie udalo sie wykonac polecenia\n";
  char* invalidCommand = "Serwer: Nieprawidlowa komenda\nDostepne komendy: ls get put rm mv replace quit\n";
  char* emptyFileMessage = "Serwer: Odebrany plik jest pusty! kasowanie...\n";
  char* serverTermination = "\nSerwer: Otrzymano sygnal zakonczenia serwera. Polaczenie zostanie zerwane\n";

  switch (iType)  {
    case 0:
      write(socket, quitMsg, strlen(quitMsg));
      break;

    case 1:
      write(socket, transferComplete, strlen(transferComplete));
      break;

    case 2:
      write(socket, getSyntax, strlen(getSyntax));
      break;

    case 3:
      write(socket, putSyntax, strlen(putSyntax));
      break;

    case 4:
      write(socket, replaceSyntax, strlen(replaceSyntax));
      break;

    case 5:
      write(socket, openingFileError, strlen(openingFileError));
      break;

    case 6:
      write(socket, commandExecutionError, strlen(commandExecutionError));
      break;

    case 7:
      write(socket, invalidCommand, strlen(invalidCommand));
      break;

    case 8:
      write(socket, emptyFileMessage, strlen(emptyFileMessage));
      break;

    case 9:
      write(socket, serverTermination, strlen(serverTermination));
      break;

    default:
      break;

  }

}