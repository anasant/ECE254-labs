/*----------------------------------------------------------------------------
 *      ECE254 Lab Task Management
 *----------------------------------------------------------------------------
 *      Name:    RT_TASK_ext.C
 *      Purpose: Interface functions for extended task management  
 *      Rev.:    V4.60
 *----------------------------------------------------------------------------
 *      This code extends the RealView Run-Time Library.
 *      Created by University of Waterloo ECE254 Lab Staff.
 *---------------------------------------------------------------------------*/

#include "rt_TypeDef.h"
#include "RTX_Config.h"
#include "rt_System.h"
#include "rt_Task.h"
#include "rt_List.h"
#include "rt_MemBox.h"
#include "rt_Robin.h"
#include "rt_HAL_CM.h"
#include "rt_Task_ext.h"

#include <stdio.h>

/*----------------------------------------------------------------------------
 *      Global Variables
 *---------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 *      Local Functions
 *---------------------------------------------------------------------------*/
/*--------------------------- rt_tsk_count_get ------------------------------*/
/* added in ECE254 lab keil_rtx */
int rt_tsk_count_get (void) {
	P_TCB p_tcb;
	int count = 0;
	int i;

	for(i = 0; i < os_maxtaskrun; i++) {
		p_tcb = os_active_TCB[i];
		if (p_tcb == NULL) {
			continue;
		}
		count++;
	}
	return count;
}

/*--------------------------- rt_tsk_get ------------------------------------*/
/* added in ECE254 lab keil_proc */
OS_RESULT rt_tsk_get (OS_TID task_id, RL_TASK_INFO *p_task_info) {
	P_TCB current_task, task = 0;
	U32 sizeInAddr = (U16)os_stackinfo;
	
	task = os_active_TCB[task_id - 1];
		
	if ((!task) || (task->task_id != task_id)) {
		return OS_R_NOK;
	}

	if (task->state != 2){
		// if the task is not running
		p_task_info->stack_usage = (U8)(((U32)(task->stack) + sizeInAddr - (U32)(task->tsk_stack))*100/sizeInAddr);
	} else {
		// if the task is running
		p_task_info->stack_usage = (U8)(((U32)(task->stack) + sizeInAddr - (U32)rt_get_PSP())*100/sizeInAddr);
	}
	
		p_task_info->task_id     = task->task_id;
		p_task_info->state       = task->state;
		p_task_info->prio        = task->prio;
		p_task_info->ptask       = task->ptask;
	
	return OS_R_OK;
}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
