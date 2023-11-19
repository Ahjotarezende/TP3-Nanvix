#include <nanvix/const.h>
#include <sys/sem.h>

int getval (int semaphore_id)
{
    for (int i = 0; i < SEM_MAX; i++) {
        if (semtab[i].state == ACTIVE) { 
            if (semtab[i].id == semaphore_id) {
                if (check_valid(&semtab[i]) == -1) return -1;
                return semtab[i].value;
            }
        }
    }
    return -1;
}

int setval (int semaphore_id, int values)
{
    for (int i = 0; i < SEM_MAX; i++) {
        if (semtab[i].state == ACTIVE) 
            if (semtab[i].id == semaphore_id) {
                if (check_valid(&semtab[i]) == -1) return -1;
                semtab[i].value = values;
                return 0;
            }
    }
    return -1;
}

int ipc_rmid (int semaphore_id)
{
    for (int i = 0; i < SEM_MAX; i++) {
        if (semtab[i].state == ACTIVE) { 
            if (semtab[i].id == semaphore_id) {
                if (check_valid(&semtab[i]) == -1) return -1;

                struct semaphore *sem = &semtab[i]; 
                int table = sem->position / 16; 
                int pos_table = sem->position % 16; 
                int comp = 1;
                comp = comp << pos_table; 
                int *b = &curr_proc->shared_sem[table]; 
                *b = *b & (~comp);
                sem->procuse--;

                if (sem->procuse == 0) {
                    sem->state = INACTIVE;
                    return 0;
                }
                return 0;
            }
        }
    }
    return -1;
}

PUBLIC int sys_semctl (int semaphore_id, int cmd, int values)
{
    switch (cmd) {
        case GETVAL:
            return getval(semaphore_id);
        case SETVAL:
            return setval(semaphore_id, values);
        case IPC_RMID:
            return ipc_rmid(semaphore_id);
    }
    return -1;
}