/**
  * ECE254 Linux Dynamic Memory Management Lab
  * @file: main_test.c
  * @brief: The main file to write tests of memory allocation algorithms
  */ 

/* includes */
/* system provided header files. You may add more */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* non-system provided header files. 
   Do not include more user-defined header files here
 */
#include "mem.h"

//---------------------------------------------------//
//            Mem Helper Functions                   //
//---------------------------------------------------//
int memory_init_test(size_t size, int algo) {
	if (algo == 0) {
		return best_fit_memory_init(size);
	} else {
		return worst_fit_memory_init(size);
	}
}

void* mem_alloc_test(size_t size, int algo) {
	if (algo == 0) {
		return best_fit_alloc(size);
	} else {
		return worst_fit_alloc(size);
	}
}

void mem_dealloc_test(void *ptr, int algo) {
	if (algo == 0) {
		best_fit_dealloc(ptr);
	} else {
		worst_fit_dealloc(ptr);
	}
}

int mem_extfrag_test(int num, int algo) {
	if (algo == 0) {
		return best_fit_count_extfrag(num);
	} else {
		return worst_fit_count_extfrag(num);
	}
}

node* mem_head(int algo) {
	if (algo == 0) {
		return head_bf;
	} else {
		return head_wf;
	}
}

//---------------------------------------------------//
//                  Test Cases                       //
//---------------------------------------------------//
void test_not_split_easy(int algo) {
	printf("test_not_split_easy: ");
	void* mem = mem_alloc_test(8*1024, algo);
	node* head = mem_head(algo);

	printf("%d ", head->size == 8*1024);
	printf("%d ", head->is_allocated == 1); // true
	printf("%d ", head->next == NULL);
	printf("%d ", head->previous == NULL);

	mem_dealloc_test(mem, algo);
	printf("\n");
}

void test_not_split_hard(int algo) {
	printf("test_not_split_hard: ");
	void* mem = mem_alloc_test(8*1024 - sizeof(node), algo);
	node* head = mem_head(algo);

	printf("%d ", head->size == 8*1024);
	printf("%d ", head->is_allocated == 1); // true
	printf("%d ", head->next == NULL);
	printf("%d ", head->previous == NULL);

	mem_dealloc_test(mem, algo);
	printf("\n");
}

void test_left_deallocate(int algo) {
	printf("test_left_deallocate: ");
	void* mem = mem_alloc_test(7*1024, algo);
	node* head = mem_head(algo);

	printf("%d ", head->size == 7*1024);
	printf("%d ", head->is_allocated == 1);
	printf("%d ", head->next != NULL);
	printf("%d ", head->next->size == 1024 - sizeof(node));
	printf("%d ", head->next->is_allocated == 0);
	printf("%d ", head->previous == NULL);

	void* mem2 = mem_alloc_test(1024 - sizeof(node), algo);
	printf("%d ", head->size == 7*1024);
	printf("%d ", head->is_allocated == 1);
	printf("%d ", head->next != NULL);
	printf("%d ", head->next->size == 1024 - sizeof(node));
	printf("%d ", head->next->is_allocated == 1);
	printf("%d ", head->previous == NULL);

	mem_dealloc_test(mem, algo);
	printf("%d ", head->is_allocated == 0);
	printf("%d ", head->next != NULL);
	printf("%d ", head->next->size == 1024 - sizeof(node));
	printf("%d ", head->next->is_allocated == 1);
	printf("%d ", head->previous == NULL);

	mem_dealloc_test(mem2, algo);
	printf("%d ", head->size == 8*1024);
	printf("%d ", head->is_allocated == 0);
	printf("%d ", head->next == NULL);
	printf("%d ", head->previous == NULL);
	printf("\n");
}

void test_right_deallocate(int algo) {
	printf("test_right_deallocate: ");
	void* mem = mem_alloc_test(7*1024, algo);
	node* head = mem_head(algo);

	printf("%d ", head->size == 7*1024);
	printf("%d ", head->is_allocated == 1);
	printf("%d ", head->next != NULL);
	printf("%d ", head->next->size == 1024 - sizeof(node));
	printf("%d ", head->next->is_allocated == 0);
	printf("%d ", head->previous == NULL);

	void* mem2 = mem_alloc_test(1024 - sizeof(node), algo);
	printf("%d ", head->size == 7*1024);
	printf("%d ", head->is_allocated == 1);
	printf("%d ", head->next != NULL);
	printf("%d ", head->next->size == 1024 - sizeof(node));
	printf("%d ", head->next->is_allocated == 1);
	printf("%d ", head->previous == NULL);

	mem_dealloc_test(mem2, algo);
	printf("%d ", head->is_allocated == 1);
	printf("%d ", head->next != NULL);
	printf("%d ", head->next->size == 1024 - sizeof(node));
	printf("%d ", head->next->is_allocated == 0);
	printf("%d ", head->previous == NULL);

	mem_dealloc_test(mem, algo);
	printf("%d ", head->size == 8*1024);
	printf("%d ", head->is_allocated == 0);
	printf("%d ", head->next == NULL);
	printf("%d ", head->previous == NULL);
	printf("\n");
}

// test middle deallocate
void test_middle_deallocate(int algo) {
	printf("test_middle_deallocate: ");
	void* mem = mem_alloc_test(3*1024, algo);
	node* head = mem_head(algo);

	printf("%d ", head->size == 3*1024);
	printf("%d ", head->is_allocated == 1);
	printf("%d ", head->next != NULL);
	printf("%d ", head->next->size == 5*1024 - sizeof(node));
	printf("%d ", head->next->is_allocated == 0);
	printf("%d ", head->previous == NULL);

	void* mem2 = mem_alloc_test(2*1024 - sizeof(node), algo);
	printf("%d ", head->next != NULL);
	printf("%d ", head->next->size == 2*1024 - sizeof(node));
	printf("%d ", head->next->is_allocated == 1);
	printf("%d ", head->next->previous != NULL);

	void* mem3 = mem_alloc_test(3*1024 - sizeof(node), algo);
	printf("%d ", head->next->next != NULL);
	printf("%d ", head->next->next->size == 3*1024 - sizeof(node));
	printf("%d ", head->next->next->is_allocated == 1);
	printf("%d ", head->next->next->previous != NULL);

	mem_dealloc_test(mem3, algo);
	printf("%d ", head->is_allocated == 1);
	printf("%d ", head->next->next->size == 3*1024 - sizeof(node));
	printf("%d ", head->next->size == 2*1024 - sizeof(node));
	printf("%d ", head->next->next->is_allocated == 0);
	printf("%d ", head->next->is_allocated == 1);
	printf("%d ", head->previous == NULL);
	printf("%d ", head->next != NULL);

	mem_dealloc_test(mem, algo);
	printf("%d ", head->is_allocated == 0);
	printf("%d ", head->size == 3*1024);
	printf("%d ", head->previous == NULL);
	printf("%d ", head->next != NULL);

	mem_dealloc_test(mem2, algo);
	printf("%d ", head->is_allocated == 0);
	printf("%d ", head->next == NULL);
	printf("%d ", head->previous == NULL);
	printf("%d ", head->size == 8*1024);

	printf("\n");
}

// test the hole it chooses is the correct one
void test_allocation(int algo) {
	printf("test_allocation: ");
	node* head = mem_head(algo);
	void* mem = mem_alloc_test(1*1024, algo);
	void* mem2 = mem_alloc_test(5*1024 - sizeof(node), algo);
	void* mem3 = mem_alloc_test(2*1024 - sizeof(node), algo);
	
	mem_dealloc_test(mem, algo);
	mem_dealloc_test(mem3, algo);

	void* mem4 = mem_alloc_test(1024 - sizeof(node), algo);
	if (algo == 0) { // should choose first hole for best fit
		printf("%d ", head->is_allocated == 1);
		printf("%d ", head->next->is_allocated == 1);
		printf("%d ", head->next->next->is_allocated == 0);
	} else { // should choose 3rd hole for worst fit
		printf("%d ", head->is_allocated == 0);
		printf("%d ", head->next->is_allocated == 1);
		printf("%d ", head->next->next->is_allocated == 1);
	}
	mem_dealloc_test(mem4, algo);

	void* mem5 = mem_alloc_test(1034, algo);
	// should choose 3rd hole
	printf("%d ", head->is_allocated == 0);
	printf("%d ", head->next->is_allocated == 1);
	printf("%d ", head->next->next->is_allocated == 1);

	mem_dealloc_test(mem5, algo);
	mem_dealloc_test(mem2, algo);

	printf("\n");
}

void test_efficiency(int algo) {
	srand(12345);
	void** ptrs = calloc(200, sizeof(void*));
	node* head = mem_head(algo);

	// do a series of 50000 allocations and deallocations
	for(int i = 0; i < 50000; i++) {
		if(rand() % 2 == 0) {
			for(int j = 0; j < 200; j++) {
				int index = rand() % 200;
				if(!ptrs[index]) {
					ptrs[index] = mem_alloc_test(rand() % 192, algo); // if it fails, it's ok
					break;
				}
			}
		} else {
			for(int j = 0; j < 200; j++) {
				int index = rand() % 200;
				if(ptrs[index]) {
					mem_dealloc_test(ptrs[index], algo);
					ptrs[index] = 0;
					break;
				}
			}
		}
	}

	printf("\nfragmentation table:\n");
	for(int i = 4; i <= 192; i += 4) {
		printf("%d,%d\n", i, mem_extfrag_test(i, algo));
	}

	for(int i = 0; i < 200; i++) {
		if(ptrs[i]) {
			mem_dealloc_test(ptrs[i], algo);
			ptrs[i] = 0;
		}
	}
	printf("\n");
	printf("%d ", head->is_allocated == 0);
	printf("%d ", !head->next);
	printf("%d ", !head->previous);
	printf("%d ", head->size == 8 * 1024);
	printf("\n");
	
}
// test for efficiency
// allocate random sizes of memory
// deallocate random things
// at the end of 100 things allocated, check um that fragmentation function
// call it for a number of sizes and graph that


//---------------------------------------------------//
//                  Main                             //
//---------------------------------------------------//
int main(int argc, char *argv[]) {
	int algo = 0; // default algorithm to test is best fit  

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <0/1>. 0 for best fit and 1 for worst fit \n", argv[0]);
		exit (1);
	} else if (!strcmp(argv[1], "1") || !strcmp(argv[1], "0")) {
		algo = atoi(argv[1]);
	} else {
		fprintf(stderr, "Invalid argument, please specify 0 or 1\n");
		exit(1);
	}

	memory_init_test(8*1024 + sizeof(node), algo);
	test_not_split_easy(algo);
	test_not_split_hard(algo);
	test_left_deallocate(algo);
	test_right_deallocate(algo);
	test_middle_deallocate(algo);
	test_allocation(algo);
	test_efficiency(algo);

	return 0;
}

