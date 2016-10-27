#ifndef CORE_PIPE_H
#define CORE_PIPE_H

#include "list.h"

typedef struct elem_struct
{
	int fd;
	int len;
	char *buf;
}elem_str;

typedef node_define(core_pipe_node_struct, elem_str) core_pipe_node_type;
typedef list_node_define(core_pipe_list_struct, core_pipe_node_struct) core_pipe_list_type;

extern int g_pipe_mutex[];

extern int core_pipe_init();
extern int core_pipe();
extern int core_pipe_read(int fd, void * buf, int len);
extern int core_pipe_write(int fd, void * buf, int len);
extern int test_core_pipe();

#endif // !CORE_PIPE_H


