/*******************************************************************************
* File:     	semaphore.h
* Brief:    	Header file for semaphore.c
* Author: 		Krzysztof Koch
* Version:		V1.00
* Date created:	02/02/2016
* Last mod: 	16/03/2017
*
* Note: 		
*******************************************************************************/
#include "KrisOS.h"



#ifdef USE_SEMAPHORE
/*-------------------------------------------------------------------------------
* Function:    	sem_init
* Purpose:    	Initialise the semaphore given
* Arguments:	
* 		toInit - semaphore to initialise
* 		startVal - semaphore counter start value
* Returns: 		
*		exit status
--------------------------------------------------------------------------------*/
uint32_t sem_init(Semaphore* toInit, uint32_t startVal);



#ifdef USE_HEAP
/*-------------------------------------------------------------------------------
* Function:    	sem_create
* Purpose:    	Create a semaphore using heap and initialise it
* Arguments:	
* 		startVal - semaphore counter start value
* Returns: 		
*		pointer to the semaphore created
--------------------------------------------------------------------------------*/
Semaphore* sem_create(uint32_t startVal);



/*-------------------------------------------------------------------------------
* Function:    	sem_delete
* Purpose:    	Delete the semaphore given
* Arguments:	
* 		toDelete - semaphore to delete
* Returns: 		
*		exit status
--------------------------------------------------------------------------------*/
uint32_t sem_delete(Semaphore* toDelete);
#endif



/*-------------------------------------------------------------------------------
* Function:    	sem_try_acquire
* Purpose:    	Attempt to decrement the semaphore. Don't wait if unsucessful.
* Arguments:	
* 		toAcquire - semaphore to acquire
* Returns: 		
*		exit status. EXIT_FAILURE if semaphore can't be taken
--------------------------------------------------------------------------------*/
uint32_t sem_try_acquire(Semaphore* toAcquire);



/*-------------------------------------------------------------------------------
* Function:    	sem_acquire
* Purpose:    	Decrement the semaphore. Wait if unsuccessful.
* Arguments:	
* 		toAcquire - semaphore to acquire
* Returns: -
--------------------------------------------------------------------------------*/
uint32_t sem_acquire(Semaphore* toAcquire);



/*-------------------------------------------------------------------------------
* Function:    	sem_release
* Purpose:    	Increment the semaphore.
* Arguments:	
*		toRelease - semaphore to release
* Returns: 		
*		exit status
--------------------------------------------------------------------------------*/
uint32_t sem_release(Semaphore* toRelease);

#endif
