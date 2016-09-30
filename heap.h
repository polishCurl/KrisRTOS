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

/*-------------------------------------------------------------------------------
* Function:    	heap_init
* Purpose:    	Heap initialisation function (no init needed in this case)
* Arguments:	- 	
* Returns: 		-	
--------------------------------------------------------------------------------*/
void heap_init(void);


/*-------------------------------------------------------------------------------
* Function:    	get_free_heap_size
* Purpose:    	Return the number of bytes still available for allocation
* Arguments:	-
* Returns: 
* 		number of bytes still possible for allocation
--------------------------------------------------------------------------------*/
size_t get_free_heap_size(void);