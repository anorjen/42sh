
#include "../../headers/minishell.h"

char		*new_env_join(char *name, char *value)
{
	char	*new_env;
	char	*temp;

	temp = ft_strjoin(name, "=");
	new_env = ft_strjoin(temp, value);
	free(temp);
	return (new_env);
}

int			set_env(char *name, char *value)
{
	int		i;
	int		j;
	char	**temp;
	char	*tm;

	i = -1;
	if ((tm = new_env_join(name, value)) == NULL)
		return (1);
	while (g_sh->env[++i])
	{
		j = 0;
		while (g_sh->env[i][j] == tm[j] && tm[j] != '=')
			++j;
		if (g_sh->env[i][j] == tm[j])
			CHANGE_ENV;
	}
	j = -1;
	temp = (char**)malloc(sizeof(char*) * (i + 2));
	temp[i + 1] = NULL;
	while (++j < i)
		temp[j] = g_sh->env[j];
	temp[j] = tm;
	free(g_sh->env);
	g_sh->env = temp;
	return (1);
}
