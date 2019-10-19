
#include "set.h"

static void		delete(void)
{
	unsigned int i;

	i = 0;
	if (g_set == NULL)
		return ;
	while (g_set[i] != NULL)
		ft_strdel(&(g_set[i++]));
	ft_memdel((void**)&g_set);
}

int				set_deinit(void)
{
	char *temp;

	delete();
	while ((temp = vector_get(g_set_key, 0)) != NULL)
	{
		ft_strdel(&temp);
		vector_del(g_set_key, 0);
	}
	while ((temp = vector_get(g_set_value, 0)) != NULL)
	{
		ft_strdel(&temp);
		vector_del(g_set_value, 0);
	}
	vector_deinit(&g_set_key);
	vector_deinit(&g_set_value);
	return (1);
}