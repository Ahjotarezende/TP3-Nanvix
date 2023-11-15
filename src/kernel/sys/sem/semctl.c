#include <nanvix/const.h>
#include <nanvix/hal.h>
#include <nanvix/klib.h>
#include <nanvix/pm.h>
#include <sys/sem.h>

PUBLIC int sys_semctl(int semid, int cmd, int val){

    struct semaphore *sem;

    for (sem = SEM_FIRST; sem < SEM_LAST; sem++){
        if (sem->id == semid){
            if (cmd == GETVAL)
                return sem->current_value;       
            if (cmd == SETVAL)
                semtab[semid].value = val;     
            if (cmd == IPC_RMID){
                semtab[semid].id = -1;       
            }
        }
    }

    return 0;
    
}