

#include "alias.h"

char	*alias_get(char *key)
{
	char	*value;
	char	*str;
	int		i;

	i = 0;
	if (key == NULL || ft_strcmp(key, "") == 0)
		return (ft_strdup(""));
	while ((str = vector_get(g_alias_key, i)) != NULL)
	{
		if (ft_strcmp(str, key) == 0)
		{
			str = vector_get(g_alias_value, i);
			value = ft_strdup(str);
			return (value);
		}
		i++;
	}
	return (ft_strdup(""));
}
