#include <nanvix/const.h>
#include <nanvix/hal.h>
#include <nanvix/klib.h>
#include <nanvix/pm.h>
#include <sys/sem.h>
#include <stdio.h>

PUBLIC int sys_semget(int key){

    struct semaphore *sem;

    for (sem = SEM_FIRST; sem < SEM_LAST; sem++){
        if (sem->id == key){
            return key;
        }
    }

    semtab[key].id = key;          
    semtab[key].value = SETVAL;      
    semtab[key].current_value = SETVAL; 
    return key;

}