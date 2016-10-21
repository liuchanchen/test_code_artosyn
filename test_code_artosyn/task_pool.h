#ifndef TASK_POOL_H
#define TASK_POOL_H

#include "list.h"

#define TEMPLATE_FUNC_TOTAL_NUM 20

typedef void(*template_function_type)(void *);
typedef node_define(func_node_struct, template_function_type) function_node_type;
typedef list_node_define(func_list_struct, func_node_struct) function_list_type;

extern function_node_type template_function[TEMPLATE_FUNC_TOTAL_NUM];
extern function_list_type template_function_list;

extern int task_function_list_init();

#endif // !TASK_POOL_H

