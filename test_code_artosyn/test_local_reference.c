/*
 * 分别使用局部变量，指针传递，常量传递，局部变量传递
 * 来比较函数执行效率
 *
 * 结论：以下结论来自vs的profile：
 *		1、当两个一模一样的函数传入相同的数据的时候，第一次会比第二次慢
 *		 应该是，第二次的时候，数据已经写到cache当中去了，因此速度会快
 *		 一点
 *		 2、当局部变量采用数组的时候，其效率与传入数组的效率基本上是相同
 *		 的，因为从汇编上看，局部数组也是利用一个去寄存器去从他的基址地址
 *		 3、如果用一个局部变量去接受传入的数组中的某一位，速度会快速很多
 *		 4、传入指针往往只需要传入一个指针大小的数据，因此可以用它传入很大
 *		 的结构体，或者数组
 *		 5、从vs的编译器上看加不加const没有什么区别，不知道是不是编译器已经
 *		 自己加了优化(特别的从gcc上看也没有看出区别)
 */
#include "test_local_reference.h"
#include <string.h>
#include <stdio.h>

#define ARRAY_LEN 32*1024

//#define LOCAL_ARRAY

int test_array1[ARRAY_LEN];
int test_array2[ARRAY_LEN];

typedef struct
{
	int array_struct[ARRAY_LEN];
}array_st;

array_st array_struct1;
array_st array_struct2;

static int local_argument1(int * array);
static int local_argument2(int * array);
static int reference_argument(array_st array_struct);
static int const_argument1(const int a);
static int const_argument2(const int a);

int compare_local_reference_test_case()
{
	local_argument1(test_array1);
	local_argument2(test_array2);
	reference_argument(array_struct2);
	const_argument1(3);
	const_argument2(3);
	
	return 0;
}

/*在for循环中赋值*/
static int local_argument1(int * array)
{
	int i = 0;
/*采用局部数组的话，数据应该不会用寄存器去做，应该还是用存储器去做*/
#ifdef LOCAL_ARRAY
	int array_mem[ARRAY_LEN];
#else
	int array_mem = 0;
#endif
	for (i = 0; i < ARRAY_LEN; i++)
	{
#ifdef LOCAL_ARRAY
		array_mem[i] = array[i];
		array_mem[i]++;
#else
		array_mem = array[i];
		array_mem++;
#endif
		
	}

	return 0;
}

/*在for循环外赋值*/
static int local_argument2(int * array)
{
	int i = 0;
	int array_mem[ARRAY_LEN];

	memcpy(array_mem, array, sizeof(int)*ARRAY_LEN);
	for (i = 0; i < ARRAY_LEN; i++)
	{
		array_mem[i]++;
	}

	return 0;
}

/*
* 传入大量参数会影响速度
*/
static int reference_argument(array_st array_struct)
{
	int i = 0;
	int array_mem[ARRAY_LEN];

	memcpy(array_mem, &array_struct, sizeof(array_st));
	for (i = 0; i < ARRAY_LEN; i++)
	{
		array_mem[i]++;
	}

	return 0;
}

/*用来比较加不加const是否有区别*/
static int const_argument1(int a)
{
	int b = a;

	return 0;
}

static int const_argument2(const int a)
{
	const int b = a;

	return 0;
}