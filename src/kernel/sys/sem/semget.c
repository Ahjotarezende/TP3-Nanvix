#include <nanvix/syscall.h>
#include <sys/sem.h>

new_sem(unsigned key)
{
    struct semaphore *sem;
}

PUBLIC int sys_semget(unsigned key)
{
    return (new_sem(key));
}