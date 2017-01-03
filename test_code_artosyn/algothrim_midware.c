#include "algothrim_midware.h"
#ifndef VS_DEBUG
#include "interface"
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int alg_task_num = 0;

static int send_task_to_another_core(TaskFunction_t algothrim_task_code, TaskHande_t task_handle);

int alg_task_create(TaskFunction_t algothrim_task_code, TaskHande_t task_handle)
{
	int core_id = 0;

	alg_task_num ++;
	core_id = (alg_task_num <= (DSP_CORE_NUM - 1)) ? (alg_task_num) : (0);
#ifdef VS_DEBUG
	printf("core_id : %d\n", core_id);
#else
	debug_print("core_id : %d\n", core_id);
#endif // VS_DEBUG
	if (!core_id)
	{
#ifdef VS_DEBUG
		TASK_CREATE_DEBUG;
		printf("TASK_CREATE_DEBUG\n");
#else //create xm4 task 
		
#endif // VS_DEBUG
	}
	else// assign the task to the other core
	{
		send_task_to_another_core(algothrim_task_code, task_handle);
	}
	
	return 0;
}

static int send_task_to_another_core(TaskFunction_t algothrim_task_code, TaskHande_t task_handle)
{
	TaskFunction_t * algothrim_task_codel = NULL;

	if (NULL != algothrim_task_code)
	{
		algothrim_task_codel = (TaskFunction_t *)malloc(sizeof(TaskFunction_t));
		*algothrim_task_codel = algothrim_task_code;
		algothrim_task_code(NULL);
	}
	
	return 0;
}
