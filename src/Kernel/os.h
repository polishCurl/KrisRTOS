/*******************************************************************************
* File:     	os.h
* Brief:    	os.c header file
* Author: 		Krzysztof Koch
* Version:		V1.00
* Date created:	30/09/2016
* Last mod: 	30/09/2016
*
* Note: 		Method declarations visible to OS users for accessing its 
*				functionality
*******************************************************************************/
#include "common.h"



/*-------------------------------------------------------------------------------
* Kernel status struct
--------------------------------------------------------------------------------*/
typedef struct {
	uint8_t isRunning; 					// Flag indicating if the OS is running
	uint64_t ticks; 					// OS ticks, incremented on every timer interrupt
#ifdef SHOW_DIAGNOSTIC_DATA
#ifdef USE_MUTEX
	uint32_t maxMtxCriticalSection; 	// Longest critical section implemented using mutexes
	uint32_t totalMutexNo; 				// Total number of mutexes in use
#endif
#ifdef USE_SEMAPHORE
	uint32_t totalSemNo; 				// Total number of semaphores in use
#endif
#endif
} Kernel; 

extern Kernel KrisOS;



/*-------------------------------------------------------------------------------
* Function:    	os_init
* Purpose:    	KrisOS initialisation routine
* Arguments:	-
* Returns: 
* 		exit status		
--------------------------------------------------------------------------------*/
uint32_t os_init(void);



/*-------------------------------------------------------------------------------
* Function:    	os_start
* Purpose:    	Start the operating system by setting up the first task to run
* Arguments:	-
* Returns: 
* 		exit status	
--------------------------------------------------------------------------------*/
uint32_t os_start(void);



/*-------------------------------------------------------------------------------
* Function:		idle_task
* Purpose:    	Idle task. Lowest priority task for power saving.
* Arguments:	-
* Returns: 		-
--------------------------------------------------------------------------------*/
void idle_task(void);
