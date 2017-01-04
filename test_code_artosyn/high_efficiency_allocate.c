/*采用的显式空闲链表去分配地址，每个链表都是一种大小类的空闲块的集合
并且每种块的大小都是2的次方*/

#include "high_effiency_allocate.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

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
typedef struct
{
	int data_len;
	void * ptr;
}data_st;

#define HEAP_LEN 0x100000
#define FREE_BLOCK_MIN 8
#define FREE_BLOCK_MAX 32 * 1024 * 1024
#define FREE_BLOCK_ENTRY_NUM 16

static unsigned char heap[HEAP_LEN];
static const unsigned long long free_block_table[FREE_BLOCK_ENTRY_NUM] =
{FREE_BLOCK_MIN, 32, 64, 128, 512, 1024, 4 *1024, 16 * 1024, 32 * 1024, 64 * 1024,
128 * 1024, 512 * 1024, 1024 * 1024, 4 * 1024 * 1024, 8 * 1024 * 1024, FREE_BLOCK_MAX};
static 	list_st free_block_list[FREE_BLOCK_ENTRY_NUM];
static int cur_free_ptr = 0;
static const int free_block_entry_half_num = (FREE_BLOCK_ENTRY_NUM - 1) >> 1;
static const int free_block_entry_one_quarter_num = (FREE_BLOCK_ENTRY_NUM - 1) >> 2;
static const int free_block_entry_three_quarter_num = ((FREE_BLOCK_ENTRY_NUM - 1) >> 2) + ((FREE_BLOCK_ENTRY_NUM - 1) >> 1);
static unsigned long long free_block_value_of_half_position = 0;
static unsigned long long free_block_value_of_one_quarter_position = 0;
static unsigned long long free_block_value_of_three_quarter_position = 0;
//static float free_block_max_log = (int)(log(FREE_BLOCK_MAX) / log(2));
//static float free_block_min_log = (int)(log(FREE_BLOCK_MIN) / log(2));

static unsigned int RoundUpToPowerOf2(unsigned int x);
static unsigned long long get_approximated_size(const unsigned long long wanted_size, unsigned* table_index);
static int list_init(list_st * list);
static int list_insert(list_mem_st * list_mem, list_st * list);
static int get_list_elem_head(list_mem_st ** list_mem, list_st * list);


int high_effiency_test_case()
{
	unsigned int index = 0;
	list_st list;
	list_mem_st list_mem[8];
	list_mem_st * tmp_list_mem;
	int i = 0;
	int * allocate_ptr = NULL;

	//printf("RoundUpToPowerOf2:%d,%d\n", get_approximated_size(70 * 1024, &index), index);
	list_init(&list);
	for (i = 0;i < 8;i++)
	{
		list_mem[i].value = i;
		list_insert(&list_mem[i], &list);
	}
	tmp_list_mem = list.head.after;
	for (i = 0;i < 8;i++)
	{
	//	printf("list value:%d,%d\n", tmp_list_mem->value, list.list_count);
		tmp_list_mem = tmp_list_mem->after;
	}
	get_list_elem_head(&tmp_list_mem, &list);
	//printf("after del:%d,%d\n", tmp_list_mem->value,list.list_count);
	high_effiency_allocate_init();
	allocate_ptr = (int *)high_effiency_allocate(45 * sizeof(int));
	*allocate_ptr = 32;
	//printf("cur_free_ptr:%d,%p,heap:%p,value:%d\n", cur_free_ptr, allocate_ptr, heap, *allocate_ptr);
	//printf("size:%d\n", *(allocate_ptr - sizeof(int)));
	allocate_ptr = NULL;
	allocate_ptr = (int *)high_effiency_allocate(45 * sizeof(int) * 1024);
	*allocate_ptr = 48;
	//printf("cur_free_ptr:%d,%p,heap:%p,value:%d\n", cur_free_ptr, allocate_ptr, heap, *allocate_ptr);
	high_effiency_free(allocate_ptr);
	allocate_ptr = NULL;
#if 1
	allocate_ptr = (int *)high_effiency_allocate(45 * sizeof(int));
	*allocate_ptr = 48;
#endif
//	printf("cur_free_ptr:%d,%p,heap:%p,value:%d\n", cur_free_ptr, allocate_ptr, heap, *allocate_ptr);
//	printf("free list num:\n");
#if 0
	for (i = 0;i < FREE_BLOCK_ENTRY_NUM;i++)
	{
		printf("entry id:%d, list num:%d\n", i, free_block_list[i].list_count);
	}
#endif

	return 0;
}

int high_effiency_allocate_init()
{
	int i = 0;

	free_block_value_of_half_position = free_block_table[free_block_entry_half_num];
	free_block_value_of_one_quarter_position = free_block_table[free_block_entry_one_quarter_num];
	free_block_value_of_three_quarter_position = free_block_table[free_block_entry_three_quarter_num];
	for (i = 0; i < FREE_BLOCK_ENTRY_NUM; i ++)
	{
		list_init(&free_block_list[i]);
	}

	return 0;
}


void * high_effiency_allocate(const int wanted_size)
{
	void * allocated_ptr = NULL;
	int approximated_size = 0;
	unsigned int table_index = 0;
	list_mem_st * list_mem = NULL;

	if (wanted_size <= 0)
	{
		return NULL;
	}
//	approximated_size = RoundUpToPowerOf2(wanted_size);
//	approximated_size = (approximated_size < FREE_BLOCK_MIN) ? (FREE_BLOCK_MIN) : (approximated_size);
	approximated_size = get_approximated_size(wanted_size, &table_index);
	if (!free_block_list[table_index].list_count)
	{
		allocated_ptr = heap + cur_free_ptr + sizeof(int);
		*((unsigned char *)allocated_ptr - sizeof(int)) = approximated_size;
	}
	else
	{
		get_list_elem_head(&list_mem, &free_block_list[table_index]);
		allocated_ptr = (unsigned long long *)(list_mem->value + sizeof(int));
		printf("%llx,allocated_ptr:%p\n", list_mem->value, allocated_ptr);
		free(list_mem);
		list_mem = NULL;
	}
	cur_free_ptr += approximated_size;

	return allocated_ptr;
}

int high_effiency_free(void * ptr)
{
	int free_size = 0;
	int approximated_size = 0;
	unsigned int table_index = 0;
	list_mem_st *list_mem;

	free_size = *(int *)((int *)ptr - sizeof(int));
	approximated_size = get_approximated_size(free_size, &table_index);
	list_mem = malloc(sizeof(list_mem_st));
	list_mem->value = (unsigned long long)((unsigned long long *)ptr - sizeof(int));;
	list_insert(list_mem, &free_block_list[table_index]);

	return 0;
}

static unsigned int RoundUpToPowerOf2(unsigned int x)
{
	x = x - 1;
	x = x | (x >> 1); 
	x = x | (x >> 2); 
	x = x | (x >> 4); 
	x = x | (x >> 8); 
	x = x | (x >> 16);

	return x + 1;
}

static int get_list_block(unsigned int block_size)
{


	return 0;
}

static unsigned long long get_approximated_size(const unsigned long long wanted_size, unsigned* table_index)
{
	int approximated_size = 0;
	int i = 0;
	unsigned int difference_result = 0;
	int loop_start = 0, loop_end = 0;
	const unsigned long long one_quarter_value = free_block_value_of_one_quarter_position;
	const unsigned long long three_quarter_value = free_block_value_of_three_quarter_position;
	const unsigned long long half_value = free_block_value_of_half_position;

	if (wanted_size < FREE_BLOCK_MIN)
	{
		*table_index = 0;

		return FREE_BLOCK_MIN;
	}
	else if (wanted_size > FREE_BLOCK_MAX)
	{
		*table_index = FREE_BLOCK_ENTRY_NUM -1;

		return FREE_BLOCK_MAX;
	}
	//printf("wanted_size:%llu, front_quarter_value:%llu, last_quarter_value:%llu, half_value:%llu\n", wanted_size, one_quarter_value, three_quarter_value, half_value);
	loop_start = (wanted_size < half_value)
		? ((wanted_size < one_quarter_value) ? (0) : (free_block_entry_one_quarter_num))
		: ((wanted_size < three_quarter_value) ? (free_block_entry_half_num) : (free_block_entry_three_quarter_num));
	loop_end = (wanted_size < half_value)
		? ((wanted_size < one_quarter_value) ? (free_block_entry_one_quarter_num) : (free_block_entry_half_num))
		: ((wanted_size < three_quarter_value) ? (free_block_entry_three_quarter_num) : (FREE_BLOCK_ENTRY_NUM - 1));
	//	mid = (wanted_size < free_block_table[mid])?():()
	//if((wanted_size > free_block_table[mid])
	//printf("loop_start:%d, loop_end:%d\n", loop_start, loop_end);
	for (i = loop_start; i < loop_end; i++)
	{
		if((wanted_size > free_block_table[i]) && (wanted_size <= free_block_table[i + 1]))
		{
			*table_index = i + 1;
			return free_block_table[i + 1];
		}
	}

	return approximated_size;
}

static int list_init(list_st * list)
{
	list->head.before = NULL;
	list->head.after = &list->rear;
	list->rear.before = &list->head;
	list->rear.after = NULL;
	list->list_count = 0;

	return 0;
}

static int list_insert(list_mem_st * list_mem, list_st * list)
{
	list_mem->after = list->head.after;
	list_mem->before = &(list->head);
	list->head.after->before = list_mem;
	list->head.after = list_mem;
	list->list_count++;

	return 0;
}

static int get_list_elem_head(list_mem_st ** list_mem, list_st * list)
{
	*list_mem = list->head.after;
	list->head.after = list->head.after->after;
	list->head.after->before = &list->head;
	list->list_count--;

	return 0;
}
