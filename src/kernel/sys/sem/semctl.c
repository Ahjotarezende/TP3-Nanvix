#include <nanvix/const.h>
#include <nanvix/pm.h>
#include <nanvix/klib.h>
#include <sys/sem.h>

int setval(int semaphore_id, int value)
{
    for (int i = 0; i < SEM_LENGTH; i++)
    {
        if (semtab[i].state == 1 && semtab[i].id == semaphore_id)
        {
            semtab[i].value = value;
            return 0;
        }
    }
    return -1;
}

int getval(int semaphore_id)
{
    for (int i = 0; i < SEM_LENGTH; i++)
    {
        if (semtab[i].state == 1 && semtab[i].id == semaphore_id)
        {
            return semtab[i].value;
        }
    }
    return -1;
}

int ipc_rmid(int semaphore_id)
{
    for (int i = 0; i < SEM_LENGTH; i++)
    {
        if (semtab[i].state == 1)
        {
            if (semtab[i].id == semaphore_id)
            {
                struct semaphore *sem = &semtab[i];
                int table = sem->position / 16;
                int pos_table = sem->position % 16;
                int comp = 1;
                comp = comp << pos_table;
                int *b = &curr_proc->shared_sem[table];
                *b = *b & (~comp);
                return 0;
            }
        }
    }
    return -1;
}

PUBLIC int sys_semctl(int semaphore_id, int cmd, int value)
{
    switch (cmd)
    {
    case GETVAL:
        return getval(semaphore_id);
    case SETVAL:
        return setval(semaphore_id, value);
    case IPC_RMID:
        return ipc_rmid(semaphore_id);
    }
    return -1;
}