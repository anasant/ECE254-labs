# OS ECE 254 Lab 1
October 4, 2017
Anastasia Santasheva, Keren Chandran

This folder contains the solution to the 1.6.2 from the University of Waterloo ECE 254 Lab manual. The main file consists of five tasks, with their behaviours outlined below:

Task 1: Gets the number of running tasks

Task 2: Prints "Hello from Test Task 2" and waits 100ms

Task 3: Prints "Hello from Test Task 3" and waits 200ms

Task 4: Prints "Hello from Test Task 4" at an interval of 20ms.

Task 5: Outputs task details, specifically TID, name, priority and stack usage in a tabular format and waits 100ms

The file rt_Task_ext.c contains the definition of two functions:

os_tsk_count_get - Retrieves the number of active tasks and returns the count. This ignores tasks that are null.
os_tsk_get - Retrieves the task at a given TID. If the task exists, the TCB is copied to the supplied second argument and status OS_R_OK is returned. If the task does not exist or is NULL, then the a status of OS_R_NOK is returned.
