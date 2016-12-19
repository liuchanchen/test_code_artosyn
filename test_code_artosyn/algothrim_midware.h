#ifndef ALGOTHRIM_MIDWARE_H
#define ALGOTHRIM_MIDWARE_H

#define VS_DEBUG
#define DSP_CORE_NUM 4

typedef enum
{
	DSP_CORE_0 = 0,
	DSP_CORE_1,
	DSP_CORE_2,
	DSP_CORE_3,
	ARM_CORE
}CoreId_e;
#ifdef VS_DEBUG
typedef void(*TaskFunction_t)(void *);
typedef void * TaskHande_t;
typedef void * TaskCond_t;
#endif

#ifdef VS_DEBUG
#define TASK_CREATE_DEBUG
#endif

extern int alg_task_create(TaskFunction_t algothrim_task_code, TaskHande_t task_handle);

#endif // !ALGOTHRIM_MIDWARE_H

