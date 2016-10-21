#include "malloc_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

malloc_list_t malloc_list;

int inline malloc_list_init()
{
	malloc_list.start = NULL;
	malloc_list.end = NULL;
	malloc_list.list_size = 0;

	return 0;
}

int malloc_list_insert(malloc_item_t * malloc_item)
{
	if (0 == malloc_list.list_size)
	{
		malloc_item->next = NULL;
		malloc_list.end = malloc_item;
	}
	else
	{
		malloc_item->next = malloc_list.start;
	}
	malloc_list.start = malloc_item;
	malloc_list.list_size++;

	return 0;
}

int malloc_list_del_specific(malloc_item_t * malloc_item)
{
	malloc_item_t * tmp_malloc_item = malloc_list.start;

	if (tmp_malloc_item->index == malloc_item->index)
	{
		malloc_list.start = malloc_list.start->next;

		return 0;
	}
	while (NULL != tmp_malloc_item->next)
	{
		if (tmp_malloc_item->next->index == malloc_item->index)
		{
			tmp_malloc_item->next = tmp_malloc_item->next->next;
			malloc_list.list_size--;

			return 0;
		}
		tmp_malloc_item = tmp_malloc_item->next;
		//return -1;
	}

	return -1;
}

int inline malloc_list_max_index()
{
	return malloc_list.start->index;
}

int inline malloc_list_size()
{
	return malloc_list.list_size;
}

int test_malloc_list()
{
	int i = 0;
	int index = 0;
	malloc_item_t * malloc_item[20];
	unsigned char buf[4] = { 0x32, 0x32, 0x32, 0x32 };

	malloc_list_init();
	for ( i = 0; i < 10; i++)
	{
		malloc_item[i] = (malloc_item_t *)malloc(sizeof(malloc_item_t));
		malloc_item[i]->index = index;
		malloc_list_insert(malloc_item[i]);
		index++;
	}
	printf("list size:%d\n", malloc_list_size());
	malloc_list_del_specific(malloc_item[3]);
	printf("del result:%d\n", malloc_list_del_specific(malloc_item[3]));
	printf("cmp:%d\n", memcmp(buf, 0x32, sizeof(unsigned char)));

	return 0;
}