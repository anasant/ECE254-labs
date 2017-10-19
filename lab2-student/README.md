# OS ECE 254 Lab 1
October 18, 2017
Anastasia Santasheva, Keren Chandran

This folder contains the solution to 2.4.2 tasks from the University of Waterloo ECE 254 Lab manual. The main file consists of five tasks, with their behaviours outlined below:

Task 1: test that a task can allocate a fixed size of memory, tests a task will be blocked if there is no memory available when os_mem_alloc() is called 

Task 2: frees up memory in the stack, tests interleaving between tasks

Task 3: asks for resources from the stack when stack is full, has to wait for stack to free up memory (done by task 2); initialized with higher priority than task 4

Task 4: asks for resources from the stack when stack is full, has to wait for stack to free up memory (done by task 2); initialized with lower priority than task 3

The file rt_Task_ext.c contains the definition of two functions:

os_tsk_count_get - Retrieves the number of active tasks and returns the count. This ignores tasks that are null.
os_tsk_get - Retrieves the task at a given TID. If the task exists, the TCB is copied to the supplied second argument and status OS_R_OK is returned. If the task does not exist or is NULL, then the a status of OS_R_NOK is returned.

October 18, 2017 update: 

The file rt_Membox_ext.c contains the definition of two functions:

rt_free_box_s - Frees memory pointed by ptr, it will unblock a task that is waiting for memory.
rt_alloc_box_s - Allocates memory in a box, or blocks allocation and waits until memory is freed up.

Instead of starting from Lab 2's starter code provided by the professor, the old Lab 1 code that was previously handed in was used for development. This is because implementations of os_tsk_count_get and os_tsk_get could be used in debugging memory management implemented in Lab 2. 

Notes: 
- we need to use WAIT_MEM somewhere but not sure where yet, probably must be set somewhere in rt_MemBox_ext.c
- 