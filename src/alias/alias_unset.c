#include "alias.h"

void	alias_unset(char *key)
{
	int i;

	i = 0;
	while (g_alias_key->arr[i] != NULL)
	{
		if (ft_strcmp(key, g_alias_key->arr[i]) == 0)
		{
			free(vector_get(g_alias_key, i));
			g_alias_key->arr[i] = NULL;
			vector_del(g_alias_key, i);
			free(vector_get(g_alias_value, i));
			g_alias_value->arr[i] = NULL;
			vector_del(g_alias_value, i);
			alias_update();
			return ;
		}
		i++;
	}
	alias_update();
}
