#include "test_noload.h"
#ifdef TEST_NOLOAD
#include <stdio.h>

int test_buf[8] = { 0,1,2,3,4,5,6,7 }__attribute__();//locate test_buf to a on-chip mem

int test_noload()
{
	int i = 0;

	for (i = 0; i < sizeof(test_buf); i++)
	{
		debug_print("test_buf:%d\n", test_buf)//debug_print is defined in ceva code
	}
	debug_print("\n");

	return 0;
}

#endif // TEST_NOLOAD

