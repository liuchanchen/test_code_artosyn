#include "task_pool.h"
#include "function_call.h"
#include <string.h>
#include <stdio.h>

function_node_type template_function[TEMPLATE_FUNC_TOTAL_NUM];
function_list_type template_function_list;

void task_function_template_1(void * task_para)
{
	function_call_str st_function;
	
	memcpy(&st_function, task_para, sizeof(function_call_str));
	st_function.func_addr(st_function.func_para);
	printf("template1\n");
}

void task_function_template_2(void * task_para)
{
	function_call_str st_function;

	memcpy(&st_function, task_para, sizeof(function_call_str));
	st_function.func_addr(st_function.func_para);
	printf("template1\n");
}

void task_function_template_3(void * task_para)
{
	function_call_str st_function;

	memcpy(&st_function, task_para, sizeof(function_call_str));
	st_function.func_addr(st_function.func_para);
	printf("template1\n");
}

void task_function_template_4(void * task_para)
{
	function_call_str st_function;

	memcpy(&st_function, task_para, sizeof(function_call_str));
	st_function.func_addr(st_function.func_para);
	printf("template1\n");
}

void task_function_template_5(void * task_para)
{
	function_call_str st_function;

	memcpy(&st_function, task_para, sizeof(function_call_str));
	st_function.func_addr(st_function.func_para);
	printf("template1\n");
}


int task_function_list_init()
{
	int i = 0;

	list_init(&template_function_list);
	template_function[0].elem = task_function_template_1;
	list_insert_head(&template_function_list, &template_function[0]);
	template_function[1].elem = task_function_template_2;
	list_insert_head(&template_function_list, &template_function[1]);
	template_function[2].elem = task_function_template_3;
	list_insert_head(&template_function_list, &template_function[2]);
	template_function[3].elem = task_function_template_4;
	list_insert_head(&template_function_list, &template_function[3]);
	template_function[4].elem = task_function_template_5;
	list_insert_head(&template_function_list, &template_function[4]);

	return 0;
}

