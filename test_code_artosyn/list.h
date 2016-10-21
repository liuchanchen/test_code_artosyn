#ifndef TEST_LIST_H
#define TEST_LIST_H

#define node_define(name,type) \
struct name\
{\
    type elem;\
	struct name * next;\
	struct name * last;\
}

#define list_node_define(list_struct_name,name)  \
struct list_struct_name\
{\
	int list_elem_num;\
	struct name front;\
	struct name rear;\
}

#define list_init(list) do\
{\
	(list)->front.next = &((list)->rear);\
	(list)->front.last = &((list)->front);\
    (list)->rear.last = &((list)->front);\
	(list)->rear.next = &((list)->rear);\
	(list)->list_elem_num = 0;\
}while(0)

//insert to head
#define list_insert_head(list,elem) do\
{\
	(elem)->next = (list)->front.next;\
	(elem)->last = &((list)->front);\
	(list)->front.next->last = (elem);\
	(list)->front.next = (elem);\
	(list)->list_elem_num ++;\
}while(0)

//insert to rear
#define list_insert_rear(list,elem) do\
{\
	(elem)->next = &((list)->rear);\
	(elem)->last = (list)->rear.last;\
	(list)->rear.last->next = (elem);\
	(list)->rear.last = (elem);\
	(list)->list_elem_num ++;\
}while(0)

//delete from rear
#define list_del_rear(list) do\
{\
	(list)->rear.last->last->next = &((list)->rear);\
	(list)->rear.last = (list)->rear.last->last;\
	(list)->list_elem_num --;\
}while(0)

//delete from head
#define list_del_head(list) do\
{\
	(list)->front.next->next->last = &((list)->front);\
	(list)->front.next = (list)->front.next->next;\
	(list)->list_elem_num --;\
}while(0)

#define get_list_elem_head(list, elem) do\
{\
	(elem) = (list)->front.next;\
	list_del_head(list);\
}while(0)

#define get_list_elem_rear(list, elem) do\
{\
	(elem) = (list)->rear.last;\
	list_del_rear(list);\
}while(0)

#define list_elem_num(list)  (list)->list_elem_num

//#define find_oldest_elem(list)

extern int test_list();

#endif