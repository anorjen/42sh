/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environments.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:56:30 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:56:31 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char		*new_env(t_process *proc)
{
	char	*new_env;
	char	*temp;

	new_env = NULL;
	if (proc->query[1] == NULL)
		write(2, "setenv: not enough arguments\n", 29);
	else if (!ft_strcmp(proc->query[1], "="))
		write(2, "zsh: bad assignment\n", 20);
	else if (proc->query[2] == NULL)
	{
		if (ft_strstr(proc->query[1], "="))
			new_env = ft_strdup(proc->query[1]);
		else
			new_env = ft_strjoin(proc->query[1], "=");
	}
	else if (proc->query[3] == NULL)
	{
		temp = ft_strjoin(proc->query[1], "=");
		new_env = ft_strjoin(temp, proc->query[2]);
		free(temp);
	}
	return (new_env);
}

int			setenv_(t_process *proc)
{
	int		i;
	int		j;
	char	**temp;
	char	*tm;

	i = -1;
	if ((tm = new_env(proc)) == NULL)
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

int			remove_env(t_process *proc)
{
	int		i;
	int		j;
	int		k;
	int		count;

	i = -1;
	count = 0;
	while (g_sh->env[++i])
	{
		j = 0;
		while (proc->query[++j])
		{
			k = 0;
			while (g_sh->env[i][k] != '='
			&& proc->query[j][k] == g_sh->env[i][k])
				++k;
			if (g_sh->env[i][k] == '=')
			{
				free(g_sh->env[i]);
				g_sh->env[i] = ft_strdup("\0");
				++count;
			}
		}
	}
	return (i - count);
}

int			unset_(t_process *proc)
{
	int		j;
	int		k;
	char	**temp;
	int		count;

	if (!proc->query[1])
	{
		write(2, "unset: not enough arguments\n", 28);
		return (1);
	}
	count = remove_env(proc);
	temp = (char**)malloc(sizeof(char*) * (count + 1));
	j = 0;
	k = -1;
	while (g_sh->env[++k])
	{
		if (g_sh->env[k][0] != '\0')
			temp[j++] = g_sh->env[k];
		else
			free(g_sh->env[k]);
	}
	temp[j] = NULL;
	free(g_sh->env);
	g_sh->env = temp;
	return (1);
}

char		*get_env(char *varible)
{
	int		i;
	int		j;
	char	**environ;
	char	*str;

	i = 0;
    str = set_get(varible);
    if (!ft_strequ(str, ""))
        return (str);
	environ = g_sh->env;
	while (environ[i])
	{
		j = 0;
		while (environ[i][j] && environ[i][j] != '='
			&& varible[j] && environ[i][j] == varible[j])
			++j;
		if (environ[i][j] == '=')
			return (&environ[i][ft_strlen(varible) + 1]);
		i++;
	}
	ft_strdel(&str);
	return (NULL);
}
