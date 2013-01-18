#ifndef SIGNALS_H
#define SIGNALS_H

void signal_handler(int);                                                      /* dla SIGCHLD robi wait procesow, dla SIGINT / SIGTERM ustawia flage zamykajaca program */


#endif