#include <nanvix/const.h>
#include <sys/sem.h>
#include <nanvix/config.h>
#include <nanvix/pm.h>

PUBLIC struct semaphore semtab[SEM_LENGTH];

int init_semaphore()
{
    for (int i = 0; i < SEM_LENGTH; i++)
    {
        semtab[i].key = 0;
        semtab[i].id = i;
        semtab[i].value = 0;
        semtab[i].state = 0;
        semtab[i].priority = 0;
    }

    return 0;
}