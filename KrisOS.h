/*******************************************************************************
* File:     	KrisOS.h
* Brief:    	Interface to the KrisOS embedded operating system
* Author: 		Krzysztof Koch
* Version:		V1.00
* Date created:	30/09/2016
* Last mod: 	30/09/2016
*
* Note: 		User interface to the KrisOS and KrisOS setup parameters
*******************************************************************************/
#include "svc.h"


/*-------------------------------------------------------------------------------
* System timing setup
*------------------------------------------------------------------------------*/
/* Clock source: 
	0 - 16MHz external crystal oscilator 
	1 - 16MHz internal oscilator
	2 - 4MHz internal oscilator (can't drive the Phase-Lock Loop)
	3 - 30kHz internal oscilator (can't drive the PLL)	*/
#define CLOCK_SOURCE 0

// System clock divider (Derived frequency = (200MHz / SYSCLOCK_DIVIDER)
#define SYSCLOCK_DIVIDER 5 	

// Clock frequency in Hz
extern uint32_t OS_CLOCK_FREQ; 

// Quantum (time slice) length in number of clock cycles
#define TIME_SLICE (OS_CLOCK_FREQ / 100)



/*-------------------------------------------------------------------------------
* Task Control Block setup
*------------------------------------------------------------------------------*/
// Maximum number of tasks that can be run concurrently
#define MAX_TASKS 3

// Size of stack allocated to each of the tasts (TASK_STACK_SIZE * 8bytes)
#define TASK_STACK_SIZE 50



/*-------------------------------------------------------------------------------
* Heap Manager setup
*------------------------------------------------------------------------------*/
/* Heap manager used:
	1. Simplest, array-based no heap freeing
 	2. Linked list of free blocks, allows freeing but can lead to fragmentation */
#define HEAP_MANAGER 2

// Heap size (in bytes)
#define HEAP_SIZE 5000		



/*-------------------------------------------------------------------------------
* Serial Monitor setup (UART0 used)
*------------------------------------------------------------------------------*/
// UART0 baud rate
#define SERIAL_MONITOR_BAUD_RATE 9600	

/* UART0 word length
	0 - 5bits
	1 - 6bits
	2 - 7bits
	3 - 8bits	*/
#define SERIAL_MONITOR_WORD_LEN 3	

/* UART0 parity checking
 	0 - no parity checking
 	1 - parity bit added (even or odd) 	*/
#define SERIAL_MONITOR_D0_PARITY_CHECK 0	

/* UART0 parity
 	0 - odd
 	1 - even	*/
#define SERIAL_MONITOR_PARITY 0	

/* UART0 number of stop bits
 	0 - one stop bit
 	1 - two stop bits	*/
#define SERIAL_MONITOR_STOP_BITS 0	


/*-------------------------------------------------------------------------------
* Function:    	KrisOS_init
* Purpose:    	Initialise the operating system
* Arguments:	-
* Returns: 		-
--------------------------------------------------------------------------------*/
void __svc(SVC_OS_START) KrisOS_init(void);

