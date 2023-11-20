#include <nanvix/syscall.h>
#include <nanvix/config.h>
#include <nanvix/klib.h>
#include <nanvix/const.h>
#include <sys/sem.h>
#include <nanvix/pm.h>

int sem_down(struct semaphore *sem)
{
    while (sem->value == 0)
        sleep(curr_proc->chain, curr_proc->priority);
    if (sem->value > 0)
    {
        sem->value--;
        return 0;
    }
    return -1;
}

int sem_up(struct semaphore *sem)
{
    if (sem->value == 0)
    {
        wakeup(curr_proc->chain);
    }
    sem->value++;
    return 0;
}

PUBLIC int sys_semop(int id, int op)
{
    if (op == -1)
    {
        for (int i = 0; i < SEM_LENGTH; i++)
        {
            if (semtab[i].id == id && semtab[i].state == 1)
            {
                return sem_down(&semtab[i]);
            }
        }
        return -1;
    }
    if (op == 1)
    {
        for (int i = 0; i < SEM_LENGTH; i++)
        {
            if (semtab[i].id == id && semtab[i].state == 1)
            {
                return sem_up(&semtab[i]);
            }
        }
        return -1;
    }
    return -1;
}