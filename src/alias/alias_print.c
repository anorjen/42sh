#include "alias.h"

void	alias_print(void)
{
	int i;

	i = 0;
	while (i < (int)g_alias_value->size)
	{
		ft_printf("%s=%s\n", vector_get(g_alias_key, i),
				  vector_get(g_alias_value, i));
		i++;
	}
}