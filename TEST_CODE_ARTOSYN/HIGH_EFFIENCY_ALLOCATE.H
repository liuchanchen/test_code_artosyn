#ifndef HIGH_EFFIENCY_ALLOCATE_H

#define HIGH_EFFIENCY_ALLOCATE_H

extern int high_effiency_test_case();
extern int high_effiency_allocate_init();
extern void * high_effiency_allocate(const int wanted_size);
extern int high_effiency_free(void * ptr);

#endif

