/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:56:18 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:56:19 by mgorczan         ###   ########.fr       */
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

static void	set_pwd(void)
{
	char	new_dir[100];

	set_env("OLDPWD", get_env("PWD"));
	getcwd(new_dir, 100);
	set_env("PWD", new_dir);
}

static void	back_to_oldpwd(void)
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
		return ;
	chdir(&g_sh->env[j][7]);
	if (get_env("HOME")
		&& ft_strstr(&g_sh->env[j][7], get_env("HOME")))
		ft_printf("~%s\n", &g_sh->env[j][7 + 15]);
	else
		ft_printf("%s\n", &g_sh->env[j][7]);
	set_pwd();
}

static void	cd_ext(t_process *proc, int i)
{
	struct stat buff;

	if (!lstat(proc->query[i], &buff) && access(proc->query[i], 0) != 0)
		print_error("cd: no such file or directory: ", proc->query[i]);
	else if ((buff.st_mode & S_IFMT) != S_IFDIR)
		print_error("cd: not a directory: ", proc->query[i]);
	else
		print_error("cd: permission denied: ", proc->query[i]);
}

int			cd_(t_process *proc)
{
	int		i;
	char	*home;

	i = 1;
	proc->query[i] && !ft_strcmp(proc->query[i], "--") ? ++i : 0;
	home = get_home();
	if (proc->query[i] == NULL)
		chdir(home) != -1 ? set_pwd() : 0;
	else if (!ft_strcmp(proc->query[i], "-") && proc->query[i + 1] == NULL)
		back_to_oldpwd();
	else if (proc->query[i + 1] != NULL)
		print_error("cd: string not in pwd: ", proc->query[i]);
	else
	{
		if (chdir(proc->query[i]) == -1)
			cd_ext(proc, i);
		else
			set_pwd();
	}
	sh_update_cwd_info();
	free(home);
	return (1);
}
