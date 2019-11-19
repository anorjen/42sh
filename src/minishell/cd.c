/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:56:18 by mgorczan          #+#    #+#             */
/*   Updated: 2019/11/19 19:43:39 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char		*get_home(void)
{
	char	*path;
	char	*temp;

	path = NULL;
	temp = get_env("HOME");
	if (temp)
		path = ft_strjoin("/", temp);
	return (path);
}

static int	back_to_oldpwd(void)
{
	int	j;

	j = 0;
	while (g_sh->env[j])
	{
		if (ft_strstr(g_sh->env[j], "OLDPWD="))
			break ;
		++j;
	}
	if (!g_sh->env[j])
		return (0);
	if (chdir(&g_sh->env[j][7]) == -1)
	{
		cd_ext(&g_sh->env[j][7]);
		return (1);
	}
	if (get_env("HOME")
		&& ft_strstr(&g_sh->env[j][7], get_env("HOME")))
		ft_printf("~%s\n", &g_sh->env[j][7 + 15]);
	else
		ft_printf("%s\n", &g_sh->env[j][7]);
	set_pwd(&g_sh->env[j][7], CD_L_FLAG);
	return (0);
}

/*int			cd_(t_process *proc)
{
	int		i;
	char	*home;
	char	*flags;
	int		flag;
	int		res;

	home = get_home();
	flags = flags_parse(proc->query, &i);
	res = 0;
	if (flags)
	{
		if (!(flag = cd_check_flags(flags)))
			return (1);
	}
	if (proc->query[i] == NULL)
		chdir(home) != -1 ? set_pwd(proc->query[i], CD_P_FLAG) : 0;
	else if (!ft_strcmp(proc->query[i], "-"))
		res = back_to_oldpwd();
	else
		res = cd_path(proc->query[i], flag);
	sh_update_cwd_info();
	free(home);
	free(flags);
	ft_printf("return: %d\n", res);
	return (res);
}*/

char			*path_exp(char **dir_o)
{
	char	*tmp;
	char	*dir;
	char	*pwd;
	char	buff[PATH_MAX];

	dir = *dir_o;
	pwd = get_env("PWD");
	if (!pwd)
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
}

int				cd_(t_process *proc)
{
	char	*home;
	char	*flags;
	char	*dir;
	int		flag;
	int		i;

	home = get_env("HOME");
	flags = flags_parse(proc->query, &i);
	if (flags)
		if (!(flag = cd_check_flags(flags)))
			return (1);
	dir = ft_strdup(proc->query[i]);
	if (dir == NULL)
	{
		if (!home || ft_strequ(home, ""))
			return (0);
		else
			dir = home;
	}
	if (flag != CD_P_FLAG)
	{
		;
	}
}
