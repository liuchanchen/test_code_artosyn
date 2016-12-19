#include "test_case.h"
#include "algothrim_midware.h"
#include "test_colon_in_c_language.h"
#include "core_mutex.h"
#include "core_pipe.h"
#include "function_call.h"
#include "task_pool.h"
#include "list.h"
#include <stdio.h>

static void func(void * para);


int main(int argc, char ** argv)
{
	alg_task_create(func, NULL);
	alg_task_create(test_case_func, NULL);
	alg_task_create(NULL, NULL);
	alg_task_create(NULL, NULL);
	alg_task_create(NULL, NULL);
	//test_func();
	//test_colon_in_c_language();
	//test_core_mutex();
	//test_core_pipe();
	//test_function_call();
	//test_list();
	getchar();

	return 0;
}

static void func(void * para)
{
	unsigned int value = 0;
	unsigned int core_id = 0;
	unsigned int cnt = 0;
	unsigned int value_temp = 0;

	printf("entry func\n");
	value = 0x08800000;
	value_temp = value;
	for (cnt = 0; cnt < 5; cnt ++, value_temp = value_temp << 4)
	{
		printf("value_temp & 0x80000000:%d,%x,cnt:%d\n", value_temp & 0x80000000, value_temp, cnt);
		if (value_temp & 0x80000000)
		{
			core_id = cnt + 1;
		}
		else
		{
			continue;
		}

	}
	
	printf("test func\n");
}