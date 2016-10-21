#ifndef LIST_H
#define LIST_H

#include <stddef.h>

#ifndef NULL
#define NULL (void *)0
#endif // !NULL

typedef struct stMallocItem{
	char  func_name[32];
	size_t index;
	struct stMallocItem * next;
}malloc_item_t;
typedef struct stMallocList{
	struct stMallocItem * start;
	struct stMallocItem * end;
	size_t list_size;
}malloc_list_t;

extern int malloc_list_init();
extern int malloc_list_insert(malloc_item_t * malloc_item);
extern int malloc_list_del_specific(malloc_item_t * malloc_item);
extern int malloc_list_max_index();
extern int malloc_list_size();
extern int test_malloc_list();

#endif // !LIST_H


