/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_after_check_exist.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 13:31:08 by mgorczan          #+#    #+#             */
/*   Updated: 2020/01/12 17:53:16 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*get_full_path(char *temp, int i, int k, char *arg)
{
	char	*path;
	char	*full_path;

	path = ft_strsub(temp, i, k - i);
	full_path = ft_strnew(ft_strlen(path)
					+ ft_strlen(arg) + 1);
	full_path = ft_strcpy(full_path, path);
	ft_strcpy(full_path + ft_strlen(path), "/");
	ft_strcpy(full_path + ft_strlen(path) + 1, arg);
	free(path);
	return (full_path);
}

static char	*brute_force_exec(char *query)
{
	char	*temp;
	char	*full_path;
	int		i;
	int		k;

	i = 0;
	if (access(query, 1) != -1)
		return (ft_strdup(query));
	if ((temp = get_env("PATH")) == NULL)
		return (NULL);
	while (temp[i])
	{
		k = i;
		while (temp[k] != ':' && temp[k])
			++k;
		full_path = get_full_path(temp, i, k, query);
		if (access(full_path, 1) != -1)
			return (full_path);
		free(full_path);
		i = temp[k] != '\0' ? k + 1 : k;
	}
	return (NULL);
}

int			fork_after_check_exist(t_process *proc)
{
	char		*temp;
	struct stat	buf;

	if (!(temp = brute_force_exec(proc->query[0])))
	{
		if (lstat(proc->query[0], &buf))
			print_error("42sh: command not found: ", proc->query[0]);
		else
			print_error("42sh: permission denied: ", proc->query[0]);
		g_sh->signal = 1;
		return (1);
	}
	free(temp);
	return (0);
}
