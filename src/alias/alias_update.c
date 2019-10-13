#include "alias.h"

static void	delete(void)
{
	unsigned int i;

	i = 0;
	if (g_alias == NULL)
		return ;
	while (g_alias[i] != NULL)
		ft_strdel(&(g_alias[i++]));
	ft_memdel((void**)&g_alias);
}

static char	*join(unsigned int i)
{
	char *ret;
	char *temp;

	temp = ft_strjoin("=", g_alias_value->arr[i]);
	ret = ft_strjoin(g_alias_key->arr[i], temp);
	ft_strdel(&temp);
	return (ret);
}

void		alias_update(void)
{
	unsigned int i;

	delete();
	g_alias = (char**)ft_memalloc(sizeof(char *) * (g_alias_key->size + 1));
	if (g_alias == NULL)
		exit(-1);
	i = 0;
	while (i < g_alias_key->size)
	{
		g_alias[i] = join(i);
		i++;
	}
	g_alias[i] = NULL;
}