#include <nanvix/const.h>
#include <sys/sem.h>
#include <nanvix/config.h>
#include <nanvix/pm.h>

PUBLIC struct semaphore semtab[SEM_LENGTH];

int sem_init()
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

int check_valid (struct semaphore *sem)
{
    int table = sem->position / 16;
    int pos_table = sem->position % 16;
    int comp = 1;
    
    comp = comp << pos_table;

    int *b = &curr_proc->shared_sem[table];
    
    comp = *b & comp;

    if (comp == 0){
        return -1;
    }

    return 0;
}