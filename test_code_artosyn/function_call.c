#include "function_call.h"
#include <stdlib.h>
#include <stdio.h>

//�������Ը�RTOS����Զ���������

void task_function(void * param)
{
	printf("task function\n");
}

void call_function_frame(void * st_task_func)
{
	return 0;
}

int test_function_call()
{
	function_call_str function_call_struct;

	task_function_list_init();
	function_call_struct.func_addr = task_function;
	function_call_struct.func_para = NULL;
	task_function_template_1(&function_call_struct);
	//call_function_frame(function_call_struct.func_addr, function_call_struct.func_para);

	return 0;
}