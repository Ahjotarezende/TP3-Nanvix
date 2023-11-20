#include <nanvix/const.h>
#include <nanvix/pm.h>
#include <nanvix/klib.h>
#include <sys/sem.h>

int addedProcessOnSemaphore(struct semaphore *sem)
{
    int comp = 1;
    int pos_table = sem->position % 16;
    int table = sem->position / 16;

    comp = comp << pos_table;

    int *b = &curr_proc->shared_sem[table];

    *b = *b | comp;

    return sem->id;
}

int create_semaphore(unsigned key)
{
    struct semaphore *newsem = NULL;

    for (int i = 0; i < SEM_LENGTH; i++)
    {
        if (semtab[i].state == 0)
        {
            newsem = &semtab[i];
            break;
        }
    }

    if (newsem == NULL)
        return -1;

    newsem->key = key;
    newsem->value = 1;
    newsem->state = 1;
    newsem->priority = 0;
    newsem->procuse = 0;

    if (addedProcessOnSemaphore(newsem) == -1)
        return -1;

    return newsem->id;
}

PUBLIC int sys_semget(unsigned key)
{
    for (int i = 0; i < SEM_LENGTH; i++)
    {
        if (semtab[i].state == 1 && semtab[i].key == key)

            return addedProcessOnSemaphore(&semtab[i]);
    }
    return create_semaphore(key);
}