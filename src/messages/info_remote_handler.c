#include <string.h>
#include <unistd.h>
#include "info_remote_handler.h"
#include "../defines.h"


void info_remote_handler(int socket, int iType)  {

  char* quitMessage = "Serwer: Zakonczono polaczenie z serwerem\n";
  char* getSyntaxMessage = "\nSkladnia polecenia get:\n\nget  [LOKALNA_SCIEZKA_PLIKU_DO_WYSLANIA] [ZDALNA_NAZWA_PLIKU] [FLAGA_TRYBU]\nDostepne flagi:\n-b --binary    Binarny tryb transferu\n-t --text      Tekstowy tryb transferu\n";
  char* putSyntaxMessage = "\nSkladnia polecenia put:\n\nput  [LOKALNA_SCIEZKA_PLIKU_DO_WYSLANIA] [ZDALNA_NAZWA_PLIKU] [FLAGA_TRYBU]\nDostepne flagi:\n-b --binary    Binarny tryb transferu\n-t --text      Tekstowy tryb transferu\n";
  char* transferCompleteMessage = "Serwer: Plik zapisano pomyslnie\n";
  char* openingFileErrorMessage = "Serwer: Nie udalo sie otworzyc pliku\n";
  char* commandExecutionErrorMessage = "Serwer: Nie udalo sie wykonac polecenia\n";
  char* invalidCommandMessage = "Serwer: Nieprawidlowa komenda\nDostepne komendy: ls get put rm mv replace quit\n";
  char* emptyFileMessage = "Serwer: Odebrany plik jest pusty! kasowanie...\n";

  switch(iType)  {
    case 0:
      write(socket,quitMessage,strlen(quitMessage));
      break;

    case 1:
      write(socket,transferCompleteMessage,strlen(transferCompleteMessage));
      break;

    case 2:
      write(socket,getSyntaxMessage,strlen(getSyntaxMessage));
      break;

    case 3:
      write(socket,putSyntaxMessage,strlen(putSyntaxMessage));
      break;

    case 4:
      write(socket,openingFileErrorMessage,strlen(openingFileErrorMessage));
      break;

    case 5:
      write(socket,commandExecutionErrorMessage,strlen(commandExecutionErrorMessage));
      break;

    case 6:
      write(socket,invalidCommandMessage,strlen(invalidCommandMessage));
      break;

    case 7:
      write(socket,emptyFileMessage,strlen(emptyFileMessage));
      break;

    default:
      break;

  }


}