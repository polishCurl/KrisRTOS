/*******************************************************************************
* File:     	os.c
* Brief:    	KrisOS implementation
* Author: 		Krzysztof Koch
* Version:		V1.00
* Date created:	16/10/2016
* Last mod: 	16/10/2016
*
* Note: 	
*******************************************************************************/
#include "KrisOS.h"
#include "system.h"
#include "kernel.h"


/*-------------------------------------------------------------------------------
* Kernel status block
--------------------------------------------------------------------------------*/
Kernel KrisOS;



/*-------------------------------------------------------------------------------
* Value of exception return for SVC calls
--------------------------------------------------------------------------------*/
uint32_t svc_exc_return;



/*-------------------------------------------------------------------------------
* Function:		idle_task
* Purpose:    	Idle task. Lowest priority task for power saving.
* Arguments:	-
* Returns: 		-
--------------------------------------------------------------------------------*/
void idle_task(void) {
	while(1) __wfi();
}

// Idle task definition, the preallocated task control block and private stack
Task idleTask;
const size_t idleTaskStackSize = 100;
uint8_t idleTaskStack[idleTaskStackSize];



/*-------------------------------------------------------------------------------
* Function:    	os_init
* Purpose:    	KrisOS initialisation method
* Arguments:	-
* Returns: 		-
--------------------------------------------------------------------------------*/
void os_init(void) {

	__disable_irqs();	
	{
		// Set the initial OS state and enable the Floating-Point Unit
		KrisOS.isRunning = 0;
		__enable_fpu();
		
		// Set up the system clock
		system_clock_config(CLOCK_SOURCE, SYSCLOCK_DIVIDER);					
	
#ifdef USE_UART		
		// Initialise the uart serial interface
		uart_init(SERIAL_MONITOR_BAUD_RATE, SERIAL_MONITOR_WORD_LEN,  
				  SERIAL_MONITOR_D0_PARITY_CHECK, SERIAL_MONITOR_PARITY, 
				  SERIAL_MONITOR_STOP_BITS); 
#endif

#ifdef USE_HEAP
		// Initialise the heap
		heap_init();
#endif		

		// Initialse the scheduler
		scheduler_init();
		
		// Create system tasks:
		// 1. Idle task (priviliged, lowest possible task priority)
		task_create_static(&idleTask, idle_task, &idleTaskStack[idleTaskStackSize], TASK_PRIO_LVL_NO, 1);
		
		// Set the IRQ priority of Interrupts for task scheduling 
		// 1. SysTick (highest possible)
		// 2. SVC and PendSV (lowest possible) IRQs
		nvic_set_priority(SysTick_IRQn, 0);
		nvic_set_priority(PendSV_IRQn, 7);
		nvic_set_priority(SVCall_IRQn, 7);
	}
	__enable_irqs();	
}



/*-------------------------------------------------------------------------------
* Function:    	os_start
* Purpose:    	Start the operating system by setting up the first task to run
* Arguments:	-
* Returns: 		-
--------------------------------------------------------------------------------*/
void os_start(void) {
	
	// Helper pointer for specifying register address within the task's stack frame
	uint32_t* taskFramePtr; 	

	// Find the first task to run. 
	scheduler_run();
	scheduler.runPtr = scheduler.topPrioTask;
	scheduler.topPrioTask->status = READY;
	
	// Set the initial value of svc_exc_return, CONTROL register as well as PSP.
	// PSP should be pointing to the position of PC in the stack frame of the first task
	// to run.
	__set_psp(scheduler.runPtr->sp + (STACK_FRAME_R0 << WORD_ACCESS_SHIFT)); 
	taskFramePtr = (uint32_t*) (scheduler.runPtr->sp + (STACK_FRAME_CONTROL << WORD_ACCESS_SHIFT));
	__set_control(*taskFramePtr);
	taskFramePtr = (uint32_t*) scheduler.runPtr->sp;
	svc_exc_return = *taskFramePtr;
	
	// Initially it is assumed that the first task will run until it's time preempted
	// (will use its time slice completely)
	scheduler.status |= (1 << TIME_PREEMPT_Pos);
	
	// Set up periodic interrupts
	systick_config(SYSTEM_CLOCK_FREQ / OS_CLOCK_FREQ);	
	
	// OS is now running
	KrisOS.isRunning = 1;
}



/*-------------------------------------------------------------------------------
* Function:    	SysTick_Handler
* Purpose:    	OS 'tick' timer interrupt handler
* Arguments:	-
* Returns: 		-
--------------------------------------------------------------------------------*/
void SysTick_Handler(void) {
	
	// Increment the OS ticks counter
	OS_TICKS++;
	
	// If the soonest delayed task has become ready then wake all the currently ready tasks up
	if (scheduler.blocked != NULL && scheduler.blocked->waitCounter <= OS_TICKS)
		scheduler_wake_tasks();
	
	// If the currently running task has used up its entire time slice, then
	// it should be preempted.
	if (OS_TICKS % TIME_SLICE == 0) {
		if (scheduler.status & (1 << TIME_PREEMPT_Pos))
			scheduler_run();
		else
			scheduler.status |= (1 << TIME_PREEMPT_Pos);
	}
}



/*-------------------------------------------------------------------------------
* Function:    	SVC_Handler_C
* Purpose:    	User interface to the operating system. Part of the SVC_Handler 
* 				written in C
* Arguments:	-
* Returns: 		-
--------------------------------------------------------------------------------*/
void SVC_Handler_C(uint32_t* svcArgs) {
	
	// Extract the SVC number and use it to run the right subroutine using the 
	// arguments saved on the stack
	uint8_t svcNumber = ((uint8_t*) svcArgs[6])[-2];
	switch(svcNumber) {
// ---- OS initialisation and launch --------------------------------------------
		case SVC_OS_INIT: os_init(); break;
		case SVC_OS_START: os_start(); break;	
// ---- Interrupt control SVC calls ---------------------------------------------
		case SVC_IRQ_EN: 
			nvic_enable_irq((IRQn_Type) svcArgs[0]);
			svcArgs[0] = EXIT_SUCCESS;
			break;
		case SVC_IRQ_DIS: 
			nvic_disable_irq((IRQn_Type) svcArgs[0]);
			svcArgs[0] = EXIT_SUCCESS;
			break;
		case SVC_IRQ_SET_PEND: 
			nvic_set_pending((IRQn_Type) svcArgs[0]);
			svcArgs[0] = EXIT_SUCCESS;
			break;
		case SVC_IRQ_CLEAR_PEND: 
			nvic_clear_pending((IRQn_Type) svcArgs[0]);
			svcArgs[0] = EXIT_SUCCESS;
			break;
		case SVC_IRQ_READ_ACTIVE: svcArgs[0] = nvic_read_active((IRQn_Type) svcArgs[0]);
			break;
		case SVC_IRQ_SET_PRIO: 
			if (nvic_irq_prio_check(svcArgs[1]))
				svcArgs[0] = EXIT_FAILURE;
			else {
				nvic_set_priority((IRQn_Type) svcArgs[0], svcArgs[1]);
				svcArgs[0] = EXIT_SUCCESS;
			}
			break;		
		case SVC_IRQ_GET_PRIO: svcArgs[0] = nvic_get_priority((IRQn_Type) svcArgs[0]);
			break;		
// ---- Task scheduling SVC calls -----------------------------------------------
		case SVC_TASK_NEW: 	
			#ifdef USE_HEAP	
				svcArgs[0] = (uint32_t) task_create_dynamic((void*) svcArgs[0], svcArgs[1], svcArgs[2], 0); 
			#endif
			break;
		case SVC_TASK_NEW_S: svcArgs[0] = task_create_static((void*) svcArgs[0], (void*) svcArgs[1],  
														     (void*) svcArgs[2], svcArgs[3], 0); break;
		case SVC_TASK_SLEEP: svcArgs[0] = task_sleep(svcArgs[0]);  break;
		case SVC_TASK_YIELD: scheduler_run(); break;
		case SVC_TASK_DELETE: task_delete(); break;
// ---- Heap management functions -----------------------------------------------
		case SVC_HEAP_ALLOC: 
			#ifdef USE_HEAP	
				svcArgs[0] = (uint32_t) malloc(svcArgs[0]); 
			#endif
			break;
		case SVC_HEAP_FREE: 
			#ifdef USE_HEAP		
				free((void*) svcArgs[0]);
			#endif
			break;
// ---- Mutual exclusion lock management functions ------------------------------
		case SVC_MTX_INIT: 
			#ifdef USE_MUTEX			
				svcArgs[0] = mutex_init((void*) svcArgs[0]); 
			#endif	
			break;
		case SVC_MTX_CREATE: 
			#ifdef USE_MUTEX	
				svcArgs[0] = (uint32_t) mutex_create();
			#endif
			break;
		case SVC_MTX_TRY_LOCK: 
			#ifdef USE_MUTEX	
				svcArgs[0] = (uint32_t) mutex_try_lock((void*) svcArgs[0]);
			#endif
			break;
		case SVC_MTX_LOCK: 
			#ifdef USE_MUTEX	
				svcArgs[0] = (uint32_t) mutex_lock((void*) svcArgs[0]);
			#endif
			break;
		case SVC_MTX_UNLOCK: 
			#ifdef USE_MUTEX	
				svcArgs[0] = (uint32_t) mutex_unlock((void*) svcArgs[0]);
			#endif
			break;
		case SVC_MTX_DELETE: 
			#ifdef USE_MUTEX
				svcArgs[0] = (uint32_t) mutex_delete((void*) svcArgs[0]);
			#endif
			break;
		default: break;
	}
	return;
}
