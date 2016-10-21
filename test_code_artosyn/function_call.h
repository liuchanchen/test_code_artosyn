#ifndef _FUNCTION_CALL
#define _FUNCTION_CALL

typedef void(*task_func_type)(void *);

typedef struct 
{
	task_func_type func_addr;
	void * func_para;
}function_call_str;

extern int test_function_call();

#endif // !_FUNCTION_CALL

