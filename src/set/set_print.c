
#include "set.h"

void	set_print(void)
{
	int i;

	i = 0;

	while (i < (int)g_set_value->size)
	{
		ft_printf("%s=%s\n", vector_get(g_set_key, i),
				  vector_get(g_set_value, i));
		i++;
	}
}