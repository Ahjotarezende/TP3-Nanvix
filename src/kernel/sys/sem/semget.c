#include <nanvix/const.h>
#include <nanvix/pm.h>
#include <nanvix/klib.h>
#include <sys/sem.h>

int associate_semaphore(struct semaphore *sem)
{
    int table = sem->position / 16;     /* Encontra em qual tabela o semáforo está */
    int pos_table = sem->position % 16; /* Descobre a posição do semáforo na tabela */
    int comp = 1;

    comp = comp << pos_table; /* Posiciona o valor 1 no bit que será alterado */

    int *b = &curr_proc->shared_sem[table]; /* Pega a tabela que o semáforo está */

    *b = *b | comp; /* Atribui o valor da tabela a operação de set bit */

    sem->procuse++;

    return sem->id;
}

/**
 *  @brief Cria um novo semáforo.
 */
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

    if (associate_semaphore(newsem) == -1)
        return -1;

    return newsem->id;
}

PUBLIC int sys_semget(unsigned key)
{
    // Busca o semáforo com o key informado.
    for (int i = 0; i < SEM_LENGTH; i++)
    {
        if (semtab[i].state == 1)
            if (semtab[i].key == key)
            {
                return associate_semaphore(&semtab[i]);
            }
    }
    // Cria um semáforo.
    return create_semaphore(key);
}