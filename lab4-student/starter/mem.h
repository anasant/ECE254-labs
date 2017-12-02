/**
 * @file: memory.h
 * @brief: ECE254 Lab: memory allocators
 * @author: Anastasia Santasheva
 * @date: 2017-12-02
 */

#ifndef MEM_H_
#define MEM_H_

#include <stddef.h>

typedef struct node_struct {
	int size;     	   // size of memory in node
	int is_allocated;     // 1 means occupied, 0 means not occupied
	struct node_struct* next; // pointer to next node
	struct node_struct* previous;  // pointer to the previous node
} node;

int size_of_struct_node;
/* memory initializers */
int best_fit_memory_init(size_t size);
int worst_fit_memory_init(size_t size);

/* memory allocators */
void *best_fit_alloc(size_t size);
void *worst_fit_alloc(size_t size);

/* memory de-allocators, immediate coalesce */
void best_fit_dealloc(void *ptr);
void worst_fit_dealloc(void *ptr);

/* memory algorithm metric utility function(s) */

/* count how many contiguous bytes are less than 32B */ 
int best_fit_count_extfrag(size_t size);
int worst_fit_count_extfrag(size_t size);
int fit_count_extfrag(size_t size, node* head);

#endif // !MEM_H_
