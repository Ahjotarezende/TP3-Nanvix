/*
 * Copyright(C) 2011-2016 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 *
 * This file is part of Nanvix.
 *
 * Nanvix is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Nanvix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Nanvix. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SEM_H_
#define SEM_H_

/**
 * @brief Comand values for semaphores.
 */
/**@{*/
#include <nanvix/config.h>
#include <nanvix/const.h>
#define GETVAL 0   /**< Returns the value of a semaphore. */
#define SETVAL 1   /**< Sets the value of a semaphore.    */
#define IPC_RMID 3 /**< Destroys a semaphore.            */
#define SEM_MAX  10  				
#define SEM_FIRST ((&semtab[0]))			
#define SEM_LAST ((&semtab[SEM_MAX - 1]))	
/**@}*/

struct semaphore
{
	unsigned key; /**< Semaphore key. */
	int id;		  /**< Semaphore ID.  */
	int value;	  /**< Semaphore value. */
	int state;	  /**< Semaphore state. */
};

/* Forward definitions. */
extern int semget(unsigned);
extern int semctl(int, int, int);
extern int semop(int, int);

EXTERN struct sempahore semtab[SEM_LENGTH];

#endif /* SEM_H_ */
