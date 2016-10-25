#include "core_pipe.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FD 256
#ifndef MIN
#define MIN(a,b) (a<b)?(a):(b)
#endif // !MIN

//添加多核的进程间通讯方式(模仿POSIX中的pipe的api形式)

int g_mutex[MAX_FD];
core_pipe_list_type core_pipe_list;

#if 0
int test_list_del_elem()
{
	int i = 0;
	int fd = -1;
	core_pipe_node_type * core_pipe_node;

	for (i = 0; i < 5; i++)
	{
		fd = core_pipe();
		printf("fd:%d\n", fd);
	}
	core_pipe_node = core_pipe_list.front.next;
	while (core_pipe_node != &core_pipe_list.rear)
	{
		printf("elem fd :%d\n", core_pipe_node->elem.fd);
		core_pipe_node = core_pipe_node->next;
	}
	core_pipe_node = core_pipe_list.front.next;
	while (core_pipe_node->elem.fd != 3)
	{
		if (core_pipe_node == core_pipe_list.rear.last)
		{
			g_mutex[3 - 1] = 0;
			return -2;
		}
		core_pipe_node = core_pipe_node->next;
	}
	list_del_elem(&core_pipe_list, core_pipe_node);
	core_pipe_node = core_pipe_list.front.next;
	while (core_pipe_node != &core_pipe_list.rear)
	{
		printf("after del elem fd :%d\n", core_pipe_node->elem.fd);
		core_pipe_node = core_pipe_node->next;
	}

	return 0;
}
#endif

//test interface
int test_core_pipe()
{
	int i = 0;
	int fd = -1;
	char buf[1024];
	int read_len = 0;

	memset(buf, 0x0, sizeof(buf));
	core_pipe_init();
	fd = core_pipe();
	printf("core_pipe:%d\n", fd);
	core_pipe_write(fd, "ajdlasjdl", strlen("ajdlasjdl"));
	read_len = core_pipe_read(fd, buf, 32);
	printf("%d,%d,%s\n", fd, read_len, buf);
	core_pipe_uninit(fd);
	
	return 0;
}

int core_pipe_init()
{
	memset(g_mutex, 0x0, sizeof(g_mutex));
	list_init(&core_pipe_list);
	core_pipe_list.rear.last->elem.fd = 0;
	core_pipe_list.front.next->elem.fd = 0;
	core_pipe_list.rear.last->elem.buf = NULL;
	core_pipe_list.front.next->elem.buf = NULL;

	return 0;
}

int core_pipe()
{
	int fd = -1;
	core_pipe_node_type * core_pipe_elem;

	core_pipe_elem = (core_pipe_node_type *)malloc(sizeof(core_pipe_node_type));
	memset(core_pipe_elem, 0x0, sizeof(core_pipe_elem));
	fd = (core_pipe_list.rear.last->elem.fd + 1) % MAX_FD;
	core_pipe_elem->elem.fd = fd;
	core_pipe_elem->elem.len = 0;
	g_mutex[fd - 1] = 0;
	list_insert_rear(&core_pipe_list, core_pipe_elem);

	return fd;
}

int core_pipe_read(int fd, void * buf, int len)
{
	int read_len = 0;
	core_pipe_node_type * core_pipe_node;

	if (NULL == buf)
	{
		return -1;
	}
	printf("read fd:%d\n", fd);
	while (1 == g_mutex[fd - 1]);
	g_mutex[fd - 1] = 1;
	core_pipe_node = core_pipe_list.front.next;
	while (core_pipe_node->elem.fd != fd)
	{
		if (core_pipe_node == core_pipe_list.rear.last)
		{
			g_mutex[fd - 1] = 0;
			return -2;
		}
		core_pipe_node = core_pipe_node->next;
	}
	read_len = MIN(len, core_pipe_node->elem.len);
	memcpy(buf, core_pipe_node->elem.buf, read_len);
	g_mutex[fd - 1] = 0;

	return read_len;
}

int core_pipe_write(int fd, void * buf, int len)
{
	core_pipe_node_type * core_pipe_node;

	if (NULL == buf)
	{
		return -1;
	}
	while (1 == g_mutex[fd - 1]);
	g_mutex[fd - 1] = 1;
	core_pipe_node = core_pipe_list.front.next;
	while (core_pipe_node->elem.fd != fd)
	{
		if (core_pipe_node == core_pipe_list.rear.last)
		{
			g_mutex[fd - 1] = 0;
			return -2;
		}
		core_pipe_node = core_pipe_node->next;
	}
	core_pipe_node->elem.buf = malloc(len);
	if (NULL == core_pipe_node->elem.buf)
	{
		g_mutex[fd - 1] = 0;
		return -3;
	}
	core_pipe_node->elem.len = len;
	memcpy(core_pipe_node->elem.buf, buf, len);
	g_mutex[fd - 1] = 0;

	return 0;
}

int core_pipe_uninit(int fd)
{
	core_pipe_node_type * core_pipe_node;

	core_pipe_node = core_pipe_list.front.next;
	while (core_pipe_node->elem.fd != fd)
	{
		if (core_pipe_node == core_pipe_list.rear.last)
		{
			g_mutex[fd - 1] = 0;
			return -2;
		}
		core_pipe_node = core_pipe_node->next;
	}
	list_del_elem(&core_pipe_list, core_pipe_node);
	free(core_pipe_node->elem.buf);
	core_pipe_node->elem.buf = NULL;
	core_pipe_node->elem.fd = -1;
	core_pipe_node->elem.len = 0;

	return 0;
}

