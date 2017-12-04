/**
 * @file memory.c
 * @brief: ECE254 Lab: memory allocation algorithm comparison template file
 * @author: Anastasia Santasheva
 * @date: 2017-12-02
 */

/* includes */
#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h>
#include "mem.h"

/* global varaiables */
node* head_wf;
node* head_bf;

//---------------------------------------------------//
//                  Initialization                   //
//---------------------------------------------------//
int memory_init(size_t size, node** head) {
	if (size <= (sizeof(node) + 4)) {
		return -1; // insufficient size
	}
	*head = malloc(size);

	if (!head) {
		return -1; // return if malloc failed
	}

	(*head)->is_allocated = 0;
	(*head)->size = size - sizeof(node);
	(*head)->next = 0;
	(*head)->previous = 0;
	
	return 0;
}

int best_fit_memory_init(size_t size) {
	return memory_init(size, &head_bf);
}

int worst_fit_memory_init(size_t size) {
	return memory_init(size, &head_wf);
}

//---------------------------------------------------//
//                  Allocation                       //
//---------------------------------------------------//
void *memory_alloc(size_t size, node* head, int best_fit) {
	if(size % 4 != 0) {
		size += (4 - (size % 4));
	}

	size_t best_size = best_fit ? INT_MAX : 0; // for best fit, size should be smaller  than this BUT larger than size; for worst_fit, size should be bigger than this AND larger than size
	node* best = NULL;

	do {
		// traverses the linked list and finds the best node to use for each algorithm
		if (!head->is_allocated && ((best_fit && head->size < best_size && head->size >= size) || (!best_fit && head->size > best_size && head->size >= size))) { // works better based on the best fit / worst fit model, based on the boolean worst_fit
			best_size = head->size;
			best = head;
		}
		head = head->next;
	} while (head != NULL);

	if (!best) {
		return NULL;
	}

	// two cases: 
	// 1) current node is exactly / 4 bytes larger than the needed space 
	// 			- set is_allocated to be 1, and return best + sizeof(node)
	// 2) current node needs to be split into two
	// 			- in addition to (1), split nodes

	best->is_allocated = 1;
	size_t size_left = best_size - size;
	if (size_left >= sizeof(node) + 4) { // the minimum possible allocation for the leftover is 4 bytes; otherwise not enough space
		node* old_next = best->next;
		best->next = (node*) (((void*) best) + size + sizeof(node)); //TODO: fix pointer arithmetic????
		best->size = size;

		(best->next)->is_allocated = 0;
		(best->next)->size = size_left - sizeof(node);
		(best->next)->next = old_next;
		(best->next)->previous = best;

		if (old_next) {
			old_next->previous = best->next;
		}
	}
	return ((void*) best) + sizeof(node);
}

void *best_fit_alloc(size_t size) {
	return memory_alloc(size, head_bf, 1);
}

void *worst_fit_alloc(size_t size) {
	return memory_alloc(size, head_wf, 0);
}

//---------------------------------------------------//
//                Deallocation                       //
//---------------------------------------------------//
void mem_dealloc(void *ptr) {
	// makes sure to get the node pointer of the header and not the memory
	node* current = (node*) ((void*)ptr - sizeof(node));
	current->is_allocated = 0; // also 1) nothing is free around me
	
	// gets the previous and next node
	int previous_free = current->previous && !(current->previous->is_allocated);
	int next_free = current->next && !(current->next->is_allocated);
	
	// 2) previous space is free
	if (previous_free && !next_free) {
		node* prev = current->previous;
		prev->size += current->size + sizeof(node);
		prev->next = current->next;
		if (current->next) {
			current->next->previous = prev;
		}
	}
	// 3) next space is free
	else if (!previous_free && next_free) {
		current->size += current->next->size + sizeof(node);
		current->next = current->next->next;
		if (current->next) {
			current->next->previous = current;
		}

	}
	// 4) both previous and next spaces are free
	else if (previous_free && next_free) {
		node* prev = current->previous; // will hold all the memory
		prev->size += current->size + current->next->size + 2*sizeof(node);
		prev->next = current->next->next;
		if (current->next->next) {
			current->next->next->previous = prev;
		}
	}	

	return;
}

void best_fit_dealloc(void *ptr) {
	mem_dealloc(ptr);
}

void worst_fit_dealloc(void *ptr) {
	mem_dealloc(ptr);
}

//---------------------------------------------------//
//     Memory algorithm metric utility function(s)   //
//---------------------------------------------------//
int fit_count_extfrag(size_t size, node* head) {
	int count = 0;
	while (head) {
		if (head->size < size && head->is_allocated == 0) {
			count++;
		}
		head = head->next;
	}
	return count;
}

int best_fit_count_extfrag(size_t size) {
	return fit_count_extfrag(size, head_bf);
}

int worst_fit_count_extfrag(size_t size) {
	return fit_count_extfrag(size, head_wf);
}
