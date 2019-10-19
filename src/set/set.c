

#include "set.h"

void	set(char *key, char *value)
{
	int		i;
	char	*str;

	i = 0;
	while ((str = vector_get(g_set_key, i)) != NULL)
	{
		if (ft_strcmp(str, key) == 0)
		{
			free(vector_get(g_set_value, i));
			vector_set(g_set_value, i, ft_strdup(value));
			set_update();
			return ;
		}
		i++;
	}
	vector_add(g_set_key, ft_strdup(key));
	vector_add(g_set_value, ft_strdup(value));
	set_update();
}