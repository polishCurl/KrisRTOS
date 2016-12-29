/*******************************************************************************
* File:     	heap_manager.c
* Brief:    	heap implementation for dynamic memory allocation
* Author: 		Krzysztof Koch
* Version:		V1.00
* Date created:	28/09/2016
* Last mod: 	04/12/2016
*
* Note: 		
*******************************************************************************/
#include "KrisOS.h"
#include "kernel.h"
#include "system.h"
#ifdef USE_HEAP



/*-------------------------------------------------------------------------------
* Heap byte alignment
*------------------------------------------------------------------------------*/
#define HEAP_BYTE_ALIGN 8 			


/*-------------------------------------------------------------------------------
* Heap size in bytes (including the currently set word alignment)
*------------------------------------------------------------------------------*/		
#define ALIGNED_HEAP_SIZE (HEAP_SIZE % HEAP_BYTE_ALIGN ? 									\
							(HEAP_SIZE + (HEAP_BYTE_ALIGN - HEAP_SIZE % HEAP_BYTE_ALIGN)) :	\
							HEAP_SIZE)
							

/*-------------------------------------------------------------------------------
* Heap free block definition
--------------------------------------------------------------------------------*/
typedef struct HeapBlock {
	size_t blockSize; 				// size in bytes
	struct HeapBlock* next; 		// pointer to the next free heap block
} HeapBlock;



/*-------------------------------------------------------------------------------
* Heap manager definition
--------------------------------------------------------------------------------*/
typedef struct HeapManager {
	size_t bytesUsed;				// Number of bytes already allocated
	HeapBlock startBlock; 			// Beginning and the end of list of free blocks
	HeapBlock endBlock;
	uint8_t heapMem[ALIGNED_HEAP_SIZE];	// Heap memory
} HeapManager;

HeapManager heap;



/*-------------------------------------------------------------------------------
* Function:    	heap_insert_free_block
* Purpose:    	Insert a new block into the list of free blocks
* Arguments:	
*		toInsert - pointer to the block to insert
* Returns: 		-
--------------------------------------------------------------------------------*/
void heap_insert_free_block(HeapBlock* toInsert) {
	
	// Iterator through the list of free blocks and the size of block to insert
	HeapBlock* iterator;
	size_t blockSize;
	blockSize = toInsert->blockSize;
	
	// Iterate through the linked list of blocks until one that has bigger size
	// is next
	iterator = &heap.startBlock;
	while (iterator->next->blockSize < blockSize) 
		iterator = iterator->next;
	
	// Insert the block
	toInsert->next = iterator->next;
	iterator->next = toInsert;
}


/*-------------------------------------------------------------------------------
* Function:    	heap_init
* Purpose:    	Heap initialisation function 
* Arguments:	- 	
* Returns: 		-	
--------------------------------------------------------------------------------*/
void heap_init(void){

	// Pointer to the first free block of data that can be used
	HeapBlock* firstBlock;
	
	// Reset the counter
	heap.bytesUsed = 0;					
	
	// Initialise the two blocks used for management, the starting and ending ones
	heap.startBlock.blockSize = 0;
	heap.startBlock.next = (void*) &heap.heapMem[0];
	heap.endBlock.blockSize = ALIGNED_HEAP_SIZE;
	heap.endBlock.next = NULL;
	
	// First free block used is placed right at the beginning of heap memory area
	// It occupies the whole heap memory and points to the endBlock
	firstBlock = (void*) &heap.heapMem[0];
	firstBlock->blockSize = ALIGNED_HEAP_SIZE;
	firstBlock->next = &heap.endBlock;
}


/*-------------------------------------------------------------------------------
* Function:    	malloc
* Purpose:    	Dynamically allocate bytesToAlloc bytes on the heap
* Arguments:	
*		bytesToAlloc - number of bytes to allocate	
* Returns: 
* 		pointer to the memory block allocated or a NULL pointer if unsuccessful
--------------------------------------------------------------------------------*/
void* malloc(size_t bytesToAlloc) {
	
	// Pointer to the memory allocated
	void* allocatedMemory;
	
	// Block pointers used for traversing the list
	HeapBlock *previousBlock, *iterator;
	
	// Pointer to a new block can be created if there is no free block closely
	// matching the number of bytes requested
	HeapBlock *subBlock;
	
	// Check if the request is valid and add extra number of bytes to the request
	// so that the HeapBlock for heap management can be stored inside the allocated
	// memory. Also ensure correct memory alignment
	if (bytesToAlloc > 0) {
		bytesToAlloc += sizeof(HeapBlock);
		bytesToAlloc = align_byte_number(bytesToAlloc);
	}
	
	// If the heap is big enough to meet the request
	if (bytesToAlloc > 0 && bytesToAlloc < ALIGNED_HEAP_SIZE) {
		
		__start_critical();
		{
			// Go through all the existing free blocks until a large enough is found
			// or we reached the endBlock 
			previousBlock = &heap.startBlock;
			iterator = heap.startBlock.next;
			
			while ((iterator->blockSize < bytesToAlloc) && (iterator->next != NULL)) {
				previousBlock = iterator;
				iterator = iterator->next;
			}
			
			// If such block exists, join its neighbours and update the pointer
			if (iterator != &heap.endBlock) {
				allocatedMemory = (void*) (((uint8_t*) previousBlock->next) + sizeof(HeapBlock));
				previousBlock->next = iterator->next;
				
				// If the difference between the requested memory size and the assigned block
				// size is too big then split the block into two and insert the unallocated
				// part to the list of heap blocks
				if (iterator->blockSize - bytesToAlloc > MIN_BLOCK_SIZE) {
					subBlock = (void*) (((uint8_t*) iterator) + bytesToAlloc);
					subBlock->blockSize = iterator->blockSize - bytesToAlloc;
					iterator->blockSize = bytesToAlloc;
					heap_insert_free_block(subBlock);
				}	
				heap.bytesUsed += iterator->blockSize;
			}
		}
		__end_critical();
	}
	return allocatedMemory;	
}



/*-------------------------------------------------------------------------------
* Function:    	free
* Purpose:    	Free the allocated block of memory
* Arguments:	
*		toFree - block of heap memory to free
* Returns: 		-
--------------------------------------------------------------------------------*/
void free(void* toFree) {
	
	// Byte array and actual heap block to free
	uint8_t* bytesToFree;
	HeapBlock* blockToFree;
	
	// Test if pointer points to heap memory
	if (toFree < (void*) &heap.heapMem[0] || toFree >= (void*) &heap.heapMem[ALIGNED_HEAP_SIZE])
		return;
	
	// If the pointer is meaninful, then cast it into heap block that shall be
	// added back to the list of free blocks. Updates the number of bytes used
	if (toFree != NULL) {
		bytesToFree = (uint8_t*) toFree;
		bytesToFree -= sizeof(HeapBlock);
		blockToFree = (HeapBlock*) bytesToFree;
		
		__start_critical();
		{
			heap_insert_free_block(blockToFree);
			heap.bytesUsed -= blockToFree->blockSize;
		}
		__end_critical();
	}
}	



/*-------------------------------------------------------------------------------
* Function:    	align_byte_number
* Purpose:    	Update the number of bytes requested for allocation so that it is 
*				compliant with the current byte alignment
* Arguments:	
* 		byteNumber - number of bytes requested
* Returns: 		
*		modified byte number to
--------------------------------------------------------------------------------*/
size_t align_byte_number(size_t byteNumber) {
	
	// Test if the number of bytes is a multiple of HEAP_BYTE_ALIGN. If not, add 
	// number of bytes necessary to enforce alignment
	size_t bytesToAlign = byteNumber % HEAP_BYTE_ALIGN;
	if (bytesToAlign)
		byteNumber += HEAP_BYTE_ALIGN - bytesToAlign;
	
	return byteNumber;
}

#endif
