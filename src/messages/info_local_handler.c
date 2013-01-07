#include <stdio.h>
#include <stdlib.h>
#include "info_local_handler.h"
#include "../defines.h"

void info_local_handler (int msgNo) {

  char* Syntax = "Skladnia: serwer_plikow [OPCJA]\n-i --interface=[ADRES_IP]    Adres, na ktorym serwer nasluchuje (domyslnie: wszystkie interfejsy)\n-p --port=[PORT]                 Numer portu, na ktorym serwer nasluchuje (opcja wymagana)\n\n";
  char* invalidSyntax = "Serwer Plikow: Nieprawidlowa Skladnia. Wywolaj program z opcja -h lub --help aby uzyskac pomoc\n";
  char* stopServerMessage = "\n\n!----------SERWER ZAKONCZYL PRACE----------!\n\n";
  char* clientStoppedConnection = ">> Klient zakonczyl polaczenie\n";
  char* transferError = "!! Blad otrzymanych danych\n";
  char* connectionTerminated = "|| Zakonczono polaczenie z klientem\n";
  switch (msgNo)  {
    case 0:
      printf("%s", Syntax);
      exit(0);
      break;

    case 1:
      printf("%s", invalidSyntax);
      exit(1);
      break;

    case 2:
      printf("%s", stopServerMessage);
      break;

    case 3:
      printf("%s", clientStoppedConnection);
      break;

    case 4:
      printf("%s", transferError);
      break;

    case 5:
      printf("%s", connectionTerminated);
      break;
  }
  fflush(stdout);

}