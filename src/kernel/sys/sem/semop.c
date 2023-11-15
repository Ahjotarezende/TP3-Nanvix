#include <nanvix/syscall.h>
#include <nanvix/config.h>
#include <nanvix/const.h>
#include <sys/sem.h>

int sem_down(int id)
{
    for (int i = 0; i < SEM_LENGTH; i++)
    {
        if (semtab[i].id == id && semtab[i].state == 1 && semtab[i].value > 0)
        {
            semtab[i].value--;
            return 0;
        }
    }
    return -1;
}

int sem_up(int id)
{
    for (int i = 0; i < SEM_LENGTH; i++)
    {
        if (semtab[i].id == id && semtab[i].state == 1 && semtab[i].value > 0)
        {
            semtab[i].value++;
            return 0;
        }
    }
    return -1;
}

PUBLIC int sys_semop(int id, int op)
{
    if (op < 0)
    {
        return (sem_down(id));
    }
    else
    {
        return (sem_up(id));
    }
}