#include <arpa/inet.h>
#include <getopt.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "input_parser.h"
#include "../defines.h"
#include "../messages/info_local_handler.h"

struct sockaddr_in input_parser(int argc_s, char **argv_s) {

  int opt;
  int i;
  struct sockaddr_in parsedArgs;
  static const char *optString = "i:p:h";                                           /*rozpoznawalne krotkie opcje dla parsera*/
  static const struct option longOpts[] = {
    {"interface", required_argument, NULL, 'i'},                                    /*tablica opcji z pelnymi nazwami opcji*/
    {"port", required_argument, NULL, 'p'},                                         /*oraz ich nazwami skrotowymi*/
    {"help", no_argument, NULL, 'h'}
    };

  memset(&parsedArgs, 0, sizeof(struct sockaddr_in) );
  parsedArgs.sin_addr.s_addr = htonl(INADDR_ANY);                                   /*domyslnie: wyszstkie interfejsy o ile uzytkownik nie poda na wejsciu adresu*/

  while ((opt = getopt_long(argc_s, argv_s, optString, longOpts, NULL )) != -1)  {
    switch (opt)  {
      case 'p':
        parsedArgs.sin_port = htons((short) atoi(optarg));
        break;

      case 'i':
        parsedArgs.sin_addr.s_addr = inet_addr(optarg);
        break;

      case 'h':
        info_local_handler(__SYNTAX_REQUEST);
        exit(0);
        break;

      default:                                                                      /*opcja tylko dla celow zgodnosci ze standardem. Nie ma prawa wystąpic*/
        break;
    }
  }
  parsedArgs.sin_family = AF_INET;

  return parsedArgs;

}