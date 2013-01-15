#ifndef SEMAPHORES_H
#define SEMAPHORES_H

#if defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)
#else
union semun  {
        int val;
        struct semid_ds* buf;
        unsigned short int* array;
};
#endif
int semaphore_create(char*, int);
void P(int, int);
void V(int, int);
void semaphore_remove(int);

#endif