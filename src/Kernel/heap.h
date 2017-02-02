/*******************************************************************************
* File:     	heap_manager.h
* Brief:    	Header file for heap_manager.c
* Author: 		Krzysztof Koch
* Version:		V1.00
* Date created:	28/09/2016
* Last mod: 	28/09/2016
*
* Note: 		malloc and free method headers are already declared in stdlib.h
*******************************************************************************/
#include "common.h"
#include "KrisOS.h"



#ifdef USE_HEAP
/*-------------------------------------------------------------------------------
* Number of bytes already allocated on heap
--------------------------------------------------------------------------------*/
extern uint32_t heapBytesUsed;



/*-------------------------------------------------------------------------------
* Function:    	heap_init
* Purpose:    	Heap initialisation function (no init needed in this case)
* Arguments:	- 	
* Returns: 		-	
--------------------------------------------------------------------------------*/
void heap_init(void);



/*-------------------------------------------------------------------------------
* Function:    	malloc
* Purpose:    	Dynamically allocate bytesToAlloc bytes of memory
* Arguments:	
*		bytesToAlloc - number of bytes to allocate on heap
* Returns: 
* 		pointer to the memory block allocated or a NULL pointer if unsuccessful
--------------------------------------------------------------------------------*/
void* malloc(size_t bytesToAlloc);



/*-------------------------------------------------------------------------------
* Function:    	free
* Purpose:    	Free the allocated block of memory
* Arguments:	
*		toFree - block of heap memory to free
* Returns: 		-
--------------------------------------------------------------------------------*/
void free(void* toFree);



/*-------------------------------------------------------------------------------
* Function:    	align_byte_number
* Purpose:    	Update the number of bytes requested for allocation so that it is 
*				compliant with the current byte alignment
* Arguments:	
* 		byteNumber - number of bytes requested
* Returns: 		
*		modified byte number to
--------------------------------------------------------------------------------*/
size_t align_byte_number(size_t byteNumber);

#endif
