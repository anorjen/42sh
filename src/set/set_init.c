
#include "set.h"

int set_init()
{
	g_set = NULL;
	g_set_key = vector_init();
	g_set_value = vector_init();
	return (1);
}
