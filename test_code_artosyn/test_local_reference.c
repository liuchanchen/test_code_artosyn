/*
 * �ֱ�ʹ�þֲ�������ָ�봫�ݣ��������ݣ��ֲ���������
 * ���ȽϺ���ִ��Ч��
 *
 * ���ۣ����½�������vs��profile��
 *		1��������һģһ���ĺ���������ͬ�����ݵ�ʱ�򣬵�һ�λ�ȵڶ�����
 *		 Ӧ���ǣ��ڶ��ε�ʱ�������Ѿ�д��cache����ȥ�ˣ�����ٶȻ��
 *		 һ��
 *		 2�����ֲ��������������ʱ����Ч���봫�������Ч�ʻ���������ͬ
 *		 �ģ���Ϊ�ӻ���Ͽ����ֲ�����Ҳ������һ��ȥ�Ĵ���ȥ�����Ļ�ַ��ַ
 *		 3�������һ���ֲ�����ȥ���ܴ���������е�ĳһλ���ٶȻ���ٺܶ�
 *		 4������ָ������ֻ��Ҫ����һ��ָ���С�����ݣ���˿�����������ܴ�
 *		 �Ľṹ�壬��������
 *		 5����vs�ı������Ͽ��Ӳ���constû��ʲô���𣬲�֪���ǲ��Ǳ������Ѿ�
 *		 �Լ������Ż�(�ر�Ĵ�gcc�Ͽ�Ҳû�п�������)
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

/*��forѭ���и�ֵ*/
static int local_argument1(int * array)
{
	int i = 0;
/*���þֲ�����Ļ�������Ӧ�ò����üĴ���ȥ����Ӧ�û����ô洢��ȥ��*/
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

/*��forѭ���⸳ֵ*/
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
* �������������Ӱ���ٶ�
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

/*�����ȽϼӲ���const�Ƿ�������*/
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