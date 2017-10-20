/**
 * @brief: ECE254 Keil ARM RL-RTX Task Management Lab starter file that calls os_tsk_get()
 * @file: main_task_exp.c
 * @date: 2015/09/13
 */
/* NOTE: This release is for students to use */

#include <LPC17xx.h>
#include "uart_polling.h" 
#include <RTL.h>
#include "../../RTX_CM3/INC/RTL_ext.h" /* extended interface header file */
#include <stdio.h>
#include <string.h>

#define NUM_FNAMES 7

const int BLOCK_NUM = 32;
const int BLOCK_BYTES = 20;
const int MAX_SIZE = BLOCK_NUM + 1;
int last_freed = BLOCK_NUM - 1;

/* Reserves memory for 32 blocks of 20-bytes. */
_declare_box(mpool, BLOCK_BYTES, BLOCK_NUM);

struct func_info {
  void (*p)();      /* function pointer */
  char name[16];    /* name of the function */
};

extern void os_idle_demon(void);
__task void task1(void);
__task void task2(void);
__task void task3(void);
__task void task4(void);
__task void init (void);
 
char *state2str(unsigned char state, char *str);
char *fp2name(void (*p)(), char *str);

U8 *mem;
int mem_block_count;
U8 *allocated_memory[BLOCK_NUM];

OS_MUT g_mut_uart;
OS_TID g_tid = 255;

char g_str[16];
char g_tsk_name[16];

struct func_info g_task_map[NUM_FNAMES] = 
{
  /* os_idle_demon function ptr to be initialized in main */
  {NULL,  "os_idle_demon"}, \
  {task1, "task1"},   \
  {task2, "task2"},   \
  {task3, "task3"},   \
  {task4, "task4"},   \
  {init,  "init" }
};

/*--------------------------- task1 ----------------------------*/
/* test that a task can allocate a fixed size of memory */
/* tests a task will be blocked if there is no memory available when os_mem_alloc() is called */
/*---------------------------------------------------------------------*/
__task void task1(void) {
	int i = 0;
	_init_box(mpool, sizeof(mpool), 20);
	for (i; i <= MAX_SIZE; i++) {
		mem_block_count++;
		if (mem_block_count == MAX_SIZE) {
			printf("- Reserving %d...\n", MAX_SIZE);
			mem = os_mem_alloc(mpool);
			printf("- Reserved %d. \n", MAX_SIZE);
		} else {
			mem = os_mem_alloc(mpool);
		}
		allocated_memory[i] = mem;
	}
	printf("- Done task1 \n");
	os_tsk_delete_self();
}

/*--------------------------- task2 ----------------------------*/
/* tests that tasks interleave correctly                          */
/* task2 must free memory when task1 gets blocked                 */
/*----------------------------------------------------------------*/
__task void task2(void) {
	OS_RESULT result;
	printf("-- Freeing... (task 2)\n");
	
	result = os_mem_free(mpool, allocated_memory[last_freed]);
	last_freed--;

	if (result == OS_R_OK) {
		printf("-- Freed memory successfully! \n");
	} else {
		printf("-- Freeing memory failed! \n");
	}
	
	printf("-- Done task2 \n");
	os_tsk_delete_self();
}

/*--------------------------- task3 ----------------------------*/
/* tests that tasks interleave correctly                          */
/* task2 must free memory when task3 gets blocked                 */
/*----------------------------------------------------------------*/
__task void task3(void) {
	printf("--- Allocating high priority task3 \n");
	mem = os_mem_alloc(mpool);
	printf("--- Allocated high priority task3 \n");
	printf("--- Done task3 \n");
	os_tsk_delete_self();
}

/*--------------------------- task4 ----------------------------*/
/* tests that tasks interleave correctly                          */
/* task2 must free memory when task4 gets blocked                 */
/*----------------------------------------------------------------*/
__task void task4(void) {
	printf("---- Allocating low priority task4 \n");
	mem = os_mem_alloc(mpool);
	printf("---- Allocated low priority task4 \n");
	printf("---- Done task4 \n");
	os_tsk_delete_self();
}

/*--------------------------- init ------------------------------------*/
/* initialize system resources and create other tasks                  */
/*----- ----------------------------------------------------------------*/
__task void init(void) {
	os_mut_init(&g_mut_uart);
  
	os_mut_wait(g_mut_uart, 0xFFFF);
	os_mut_release(g_mut_uart);

	printf("TESTING: \n 1) A task can allocate a fixed size of memory \n 2) A task will get blocked if there is no memory available when os_mem_alloc() is called \n 3) A blocked memory task will be resumed once enough memory is available in the system \n \n");
	
	g_tid = os_tsk_create(task1, 5);
	os_mut_wait(g_mut_uart, 0xFFFF);
	os_mut_release(g_mut_uart);

	g_tid = os_tsk_create(task2, 4);
	os_mut_wait(g_mut_uart, 0xFFFF);
	os_mut_release(g_mut_uart);
	
	printf("\n TESTING: \n 4) Creates multiple tasks with different priorities, all blocked and waiting for memory \n 5) When memory becomes available, tests that the highest priority task waiting the longest gets the memory first \n\n");
	g_tid = os_tsk_create(task3, 3);
	os_mut_wait(g_mut_uart, 0xFFFF);
	os_mut_release(g_mut_uart);
	
	g_tid = os_tsk_create(task4, 2);
	os_mut_wait(g_mut_uart, 0xFFFF);
	os_mut_release(g_mut_uart);
	
	g_tid = os_tsk_create(task2, 1);
	os_mut_wait(g_mut_uart, 0xFFFF);
	os_mut_release(g_mut_uart);
	
	g_tid = os_tsk_create(task2, 1);
	os_mut_wait(g_mut_uart, 0xFFFF);
	os_mut_release(g_mut_uart);

	os_tsk_delete_self(); /* task MUST delete itself before exiting */
}

/**
 * @brief: convert state numerical value to string represenation      
 * @param: state numerical value (macro) of the task state
 * @param: str   buffer to save the string representation, 
 *               buffer to be allocated by the caller
 * @return:the string starting address
 */
char *state2str(unsigned char state, char *str) {
	switch (state) {
	case INACTIVE:
		strcpy(str, "INACTIVE");
		break;
	case READY:
		strcpy(str, "READY   ");
		break;
	case RUNNING:
		strcpy(str, "RUNNING ");
		break;
	case WAIT_DLY:
		strcpy(str, "WAIT_DLY");
		break;
	case WAIT_ITV:
		strcpy(str, "WAIT_ITV");
		break;
	case WAIT_OR:
		strcpy(str, "WAIT_OR");
		break;
	case WAIT_AND:
		strcpy(str, "WAIT_AND");
		break;
	case WAIT_SEM:
		strcpy(str, "WAIT_SEM");
		break;
	case WAIT_MBX:
		strcpy(str, "WAIT_MBX");
		break;
	case WAIT_MUT:
		strcpy(str, "WAIT_MUT");
		break;
	case WAIT_MEM:
		strcpy(str, "WAIT_MEM");
		break;
	default:
		strcpy(str, "UNKNOWN");    
	}
	return str;
}

/** 
 * @brief: get function name by function pointer
 * @param: p the entry point of a function (i.e. function pointer)
 * @param: str the buffer to return the function name
 * @return: the function name string starting address
 */
char *fp2name(void (*p)(), char *str) {
	int i;
	unsigned char is_found = 0;
  
	for ( i = 0; i < NUM_FNAMES; i++) {
		if (g_task_map[i].p == p) {
			str = strcpy(str, g_task_map[i].name);  
			is_found = 1;
			break;
		}
	}
	if (is_found == 0) {
		strcpy(str, "ghost");
	}
	return str;
}

int main(void) {
	SystemInit();         /* initialize the LPC17xx MCU */
	uart0_init();         /* initilize the first UART */
  
	/* fill the fname map with os_idle_demon entry point */
	g_task_map[0].p = os_idle_demon;
	printf("Calling os_sys_init()...\n");
	os_sys_init(init);    /* initilize the OS and start the first task */
}
