#include "test_case.h"
#include <stdio.h>
#include <string.h>

struct TestStr
{
	int member1;
	int member2;
}test_struct;

const int array[4] = { 0x32, 0x41, 0x24, 0x52 };

static int test_struct_copy();
static int test_func();

void test_case_func(void * para)
{
	test_struct_copy();
	test_func();
}

static int test_struct_copy()
{
	int i = 0;
	int *addr = (int *)&test_struct;


	for (i = 0; i < 2; i++)
	{
		*(addr + i * 1) = i + 1;
	}
	printf("member1:%d, member2:%d\n", test_struct.member1, test_struct.member2);

	return 0;
}

/**
 * \brief 
 * \return 
 */
static int test_func()
{
	int * reg_addr[4];
	int * fist_addr = &(test_struct.member1);

	memcpy(reg_addr, array, sizeof(int *) * 4);
	printf("reg_addr[0]:%p, reg_addr[1]:%p\n", reg_addr[0], reg_addr[1]);
	
	return 0;
}

