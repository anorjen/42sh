/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:56:18 by sbearded          #+#    #+#             */
/*   Updated: 2019/11/28 21:32:39 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			path_concat(char **dir_o, int flag)
{
	char	*tmp;
	char	*dir;
	char	*pwd;
	char	buff[PATH_MAX];

	dir = *dir_o;
	if (flag != CD_P_FLAG)
		pwd = ft_strdup(get_env("PWD"));
	if (flag == CD_P_FLAG || !pwd)
		pwd = ft_strdup(getcwd(buff, PATH_MAX));
	if (dir[0] && dir[0] != '/')
	{
		if (pwd[ft_strlen(pwd) - 1] != '/')
		{
			tmp = pwd;
			pwd = ft_strjoin(pwd, "/");
			free(tmp);
		}
		tmp = dir;
		dir = ft_strjoin(pwd, dir);
		free(tmp);
	}
	free(pwd);
	*dir_o = dir;
}

int				cut_dot_dot(char **dir_o, int i)
{
	char	*dir;
	int		j;

	dir = *dir_o;
	j = 1;
	while (dir[i - j] != '/')
		j++;
	if (!ft_strncmp(dir + i, "/..\0", 4))
		replace_str(&dir, i - j + 1, i + 3, "");
	else if (!ft_strncmp(dir + i, "/../", 4))
		replace_str(&dir, i - j + 1, i + 4, "");
	*dir_o = dir;
	return (i - j);
}

void			path_exp(char **dir_o)
{
	int		i;

	i = 0;
	while ((*dir_o)[i])
	{
		if ((*dir_o)[i] == '/')
		{
			if (!ft_strncmp((*dir_o) + i, "//", 2))
				replace_str(dir_o, i + 1, i + 2, "");
			if (!ft_strncmp((*dir_o) + i, "/./", 3))
				replace_str(dir_o, i + 1, i + 3, "");
			else if (!ft_strncmp((*dir_o) + i, "/.\0", 3))
				replace_str(dir_o, i + 1, i + 2, "");
			else if (!ft_strncmp((*dir_o) + i, "/..", 3) && i != 0)
				i = cut_dot_dot(dir_o, i);
			else if (!ft_strncmp((*dir_o) + i, "/..", 3) && i == 0)
				replace_str(dir_o, i + 1, i + 3, "");
			else
				i++;
		}
		else
			i++;
	}
}

int				cd_exp(char *dir, int flag)
{
	path_concat(&dir, flag);
	path_exp(&dir);
	if (chdir(dir) == -1)
		return (cd_ext(dir));
	set_pwd(dir);
	return (0);
}

int				cd_(t_process *proc)
{
	char	*home;
	char	*flags;
	char	*dir;
	int		flag;
	int		i;

	home = get_env("HOME");
	flag = CD_L_FLAG;
	flags = flags_parse(proc->query, &i);
	if (flags && !(flag = cd_check_flags(flags)))
		return (1);
	dir = ft_strdup(proc->query[i]);
	if (dir == NULL)
	{
		if (!home || ft_strequ(home, ""))
			return (0);
		dir = ft_strdup(home);
	}
	else if (ft_strequ(dir, "-"))
	{
		free(dir);
		dir = ft_strdup(get_env("OLDPWD"));
	}
	return (cd_exp(dir, flag));
}
