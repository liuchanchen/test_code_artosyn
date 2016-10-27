#ifndef CORE_MUTEX_H
#define CORE_MUTEX_H

#include "list.h"

typedef node_define(core_mutex_struct, int) core_mutex_node_type;
typedef list_node_define(core_mutex_list_struct, core_mutex_struct) core_mutex_list_type;

typedef int CORE_MUTEX_ID;

extern int g_mutex[];

extern int test_core_mutex();
extern int core_mutex_init();
extern int core_mutex_lock(CORE_MUTEX_ID core_mutex_id);
extern int core_mutex_unlock(CORE_MUTEX_ID core_mutex_id);
extern int core_mutex_uninit();

#endif


