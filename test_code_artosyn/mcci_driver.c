#include "mcci_driver.h"
#include "algothrim_midware.h"
#include <stdio.h>

#ifdef VS_DEBUG 
	#define portENABLE_INTERRUPTS()
	#define portDISABLE_INTERRUPTS()
#endif


static int mcci_init()
{
	portDISABLE_INTERRUPTS();
	
	portENABLE_INTERRUPTS();

	return 0;
}

