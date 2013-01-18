#ifndef CONNECTION_HANDLING_H
#define CONNECTION_HANDLING_H



int socket_descriptor_create (void);                                           /* tworzy desktyptor gniazda */
void __connection_handler(int);                                                /* obsluguje polaczenie */
void __command_handler(struct cmdStruct*, int);                                /* obsluguje polecenia klienta */
int socket_binder(int, struct sockaddr_in);                                    /* kojarzenie gniazd */
void socket_listen(int);                                                       /* obsluga nasluchiwania */

#endif