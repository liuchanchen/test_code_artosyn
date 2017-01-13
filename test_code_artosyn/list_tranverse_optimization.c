/*
 *综述：这个c文件及对应的头文件主要是用来测试多步长搜索的效率问题
 *方法：这个用于队列中的元素是顺序排列的，如果是顺序排列，则采用多步长进行搜索，然后再采用
 *		逐步缩小步长进行搜索。这个与二分法的区别在于，二分法必须事先知道队列的长度，并且能
 *		够快速的找到队列中间的那个元素，二这个方法则不需要
 *结果：1、从ceva的profile结果上看，1步长（搜索623次）为3步长的1.79倍
 */
#include "list_tranverse_optimization.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define LIST_MEM_TEST_NUM 500
#define FIND_VALUE 323

typedef struct list_mem_t
{
	unsigned long long value;
	struct list_mem_t * before;
	struct list_mem_t * after;
}list_mem_st;
typedef struct list_t
{
	list_mem_st head;
	list_mem_st rear;
	int list_count;
}list_st;

#define find_condition(list, list_mem,cond_value) ((list_mem->before->value < cond_value) && ((tmp_list_mem->before != &(list->head))))
#define elem_iterate(list_elem) (list_elem = list_elem->before)
#define find_condition_with_step_size_3(list, list_mem,cond_value) ((list_mem->before->before->before->value < cond_value) && ((tmp_list_mem->before->before->before != &(list->head))))
#define elem_iterate_with_step_size_3(list_elem) (list_elem = list_elem->before->before->before)

static int optimizated_list_init(list_st * list);
static int optimizated_list_insert(list_mem_st * list_mem, list_st * list);
static int optimizated_get_list_elem_head(list_mem_st ** list_mem, list_st * list);
static int optimizated_tranverse(list_st* list);
static int not_optimizated_tranverse(list_st * list);

static int optimizated_list_init(list_st * list)
{
	list->head.before = NULL;
	list->head.after = &list->rear;
	list->rear.before = &list->head;
	list->rear.after = NULL;
	list->list_count = 0;
	printf("&list->head:%p, &list->rear:%p\n", &list->head, &list->rear);

	return 0;
}

static int optimizated_list_insert(list_mem_st * list_mem, list_st * list)
{
	list_mem->after = list->head.after;
	list_mem->before = &(list->head);
	list->head.after->before = list_mem;
	list->head.after = list_mem;
	list->list_count++;

	return 0;
}

static int optimizated_get_list_elem_head(list_mem_st ** list_mem, list_st * list)
{
	*list_mem = list->head.after;
	list->head.after = list->head.after->after;
	list->head.after->before = &list->head;
	list->list_count--;

	return 0;
}

int list_tranverse_optimization_test_code()
{
	list_st list;
	list_mem_st list_mem[LIST_MEM_TEST_NUM];
	int i = 0;

	optimizated_list_init(&list);
	memset(&list_mem, 0x0, sizeof(list_mem));
	for (i = 0; i < LIST_MEM_TEST_NUM;i ++)
	{
		list_mem[i].value = i;
		optimizated_list_insert(&list_mem[i], &list);
	}
	not_optimizated_tranverse(&list);

	return 0;
}

static int optimizated_tranverse(list_st* list)
{
	list_mem_st list_mem;
	list_mem_st * tmp_list_mem;
	int i = 0;

#if 0
	for (tmp_list_mem = list->rear.before; \
		find_condition(tmp_list_mem, FIND_VALUE) && (tmp_list_mem != &(list->head)); \
		elem_iterate_with_step_size_3(tmp_list_mem))
	{
		i++;
	}
#else
	tmp_list_mem = list->rear.before;
	while (find_condition_with_step_size_3(list, tmp_list_mem, FIND_VALUE))
	{
		i++;
		elem_iterate_with_step_size_3(tmp_list_mem);
	}
	while (find_condition(list, tmp_list_mem, FIND_VALUE))
	{
		i++;
		elem_iterate(tmp_list_mem);
	}
#endif
	printf("tranverse times:%d,tmp_list_mem->value:%llu\n", i, tmp_list_mem->value);

	return 0;
}

static int not_optimizated_tranverse(list_st * list)
{
	list_mem_st list_mem;
	list_mem_st * tmp_list_mem;
	int i = 0;

#if 0
	for(tmp_list_mem = list->rear.before;\
		find_condition(list, tmp_list_mem, FIND_VALUE);\
		elem_iterate(tmp_list_mem))
	{
		i++;
	}
#else
	tmp_list_mem = list->rear.before;
	while (find_condition(list, tmp_list_mem, FIND_VALUE))
	{
		i++;
		elem_iterate(tmp_list_mem);
	}
#endif
	printf("tranverse times:%d,tmp_list_mem->value:%llu\n", i, tmp_list_mem->value);

	return 0;
}
