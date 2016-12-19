#include "core_mutex.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//添加多核的进程间通讯方式(模仿POSIX中互斥锁的api形式)
//在阻塞过程中一定要添加关闭调度器的代码，目前还没有添加，待添加（16.10.29）

#define MAX_MUTEX_FD 64
#ifndef MIN
#define MIN(a,b) (a<b)?(a):(b)
#endif // !MIN

int g_mutex[MAX_MUTEX_FD];
static int core_mutex_list_init_flag = 0;
core_mutex_list_type core_mutex_list;

#define CORE_MUTEX_LIST_INIT() do{\
	memset(g_mutex, 0x0, sizeof(g_mutex));\
	list_init(&core_mutex_list);\
	core_mutex_list.rear.last->elem = 0;\
	core_mutex_list.front.next->elem = 0;\
}while(0)

int test_core_mutex()
{
	CORE_MUTEX_ID core_mutex_id = -1;
	core_mutex_node_type * core_mutex_elem;
	int i = -1;

	for (i = 0; i < 5; i++)
	{
		core_mutex_id = core_mutex_init();
		printf("core_mutex_id:%d\n", core_mutex_id);
	}
	core_mutex_elem = core_mutex_list.front.next;
	while (core_mutex_elem != &core_mutex_list.rear)
	{
		printf("elem fd :%d\n", core_mutex_elem->elem);
		core_mutex_elem = core_mutex_elem->next;
	}

	return 0;
}

CORE_MUTEX_ID core_mutex_init()
{
	CORE_MUTEX_ID core_mutex_id = -1;
	core_mutex_node_type * core_mutex_elem,* core_mutex_elem_tmp;

	core_mutex_elem = (core_mutex_node_type *)malloc(sizeof(core_mutex_node_type));
	memset(core_mutex_elem, 0x0, sizeof(core_mutex_elem));
	if (0 == core_mutex_list_init_flag)
	{
		CORE_MUTEX_LIST_INIT();
		core_mutex_list_init_flag = 1;
	}
	core_mutex_id = (core_mutex_list.rear.last->elem + 1) % MAX_MUTEX_FD;
	while (1)
	{
		core_mutex_elem_tmp = core_mutex_list.front.next;
		while ((core_mutex_elem_tmp->elem != core_mutex_id)
			&& (core_mutex_elem_tmp != &core_mutex_list.rear))
		{
			core_mutex_elem_tmp = core_mutex_elem_tmp->next;
		}
		if (core_mutex_elem_tmp != &core_mutex_list.rear)
		{
			core_mutex_id = (core_mutex_id + 1) % MAX_MUTEX_FD;
		}
		else
		{
			break;
		}
	}
	g_mutex[core_mutex_id - 1] = 0;
	core_mutex_elem->elem = core_mutex_id;
	list_insert_rear(&core_mutex_list, core_mutex_elem);

	return core_mutex_id;
}

int core_mutex_uninit(CORE_MUTEX_ID core_mutex_id)
{
	core_mutex_node_type * core_mutex_node;

	core_mutex_node = core_mutex_list.front.next;
	while (core_mutex_node->elem != core_mutex_id)
	{
		if (core_mutex_node == core_mutex_list.rear.last)
		{
			g_mutex[core_mutex_id - 1] = 0;
			return -2;
		}
		core_mutex_node = core_mutex_node->next;
	}
	list_del_elem(&core_mutex_list, core_mutex_node);
	core_mutex_node->elem = -1;
	free(core_mutex_node);
	core_mutex_node = NULL;

	return 0;
}

int core_mutex_lock(CORE_MUTEX_ID core_mutex_id)
{
	//此处应该添加关闭系统调度器的代码
	while (1 == g_mutex[core_mutex_id - 1]);
	g_mutex[core_mutex_id - 1] = 1;

	return 0;
}

int core_mutex_unlock(CORE_MUTEX_ID core_mutex_id)
{
	g_mutex[core_mutex_id - 1] = 0;
	//此处应该添加打开系统调度器的代码

	return 0;
}
