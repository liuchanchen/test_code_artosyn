//list.h test code
#include "list.h"
#include <stdio.h>

typedef node_define(node_struct, int) node_type;
typedef list_node_define(list_struct, node_struct) list_type;

list_type list;

int test_list()
{
	int i = 0;
	node_type node[10], *tmp_node;

	list_init(&list);
	for (i = 0; i < 10; i++)
	{
		node[i].elem = i;
		list_insert_head(&list, &node[i]);
	}
	printf("list len:%d\n", list_elem_num(&list));
	tmp_node = list.front.next;
	for (i = 0; i < 10; i++)
	{
		printf("i:%d,node elem:%d\n", i, tmp_node->elem);
		tmp_node = tmp_node->next;
		list_del_rear(&list);
	}
	printf("list len:%d\n", list_elem_num(&list));
	for (i = 0; i < 10; i++)
	{
		node[i].elem = i;
		list_insert_rear(&list, &node[i]);
	}
	tmp_node = list.front.next;
	for (i = 0; i < 10; i++)
	{
		printf("i:%d,node elem:%d\n", i, tmp_node->elem);
		tmp_node = tmp_node->next;
	}
	get_list_elem_head(&list, tmp_node);
	printf("node elem:%d,list num:%d\n", tmp_node->elem,list.list_elem_num);

	return 0;
}