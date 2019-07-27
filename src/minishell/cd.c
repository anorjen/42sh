/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 13:39:14 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/27 13:46:26 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*get_home(char **environ)
{
	char	*path;
	char	*temp;

	path = NULL;
	temp = get_env("HOME", environ);
	if (temp)
		path = ft_strjoin("/", temp);
	return (path);
}

static void	set_pwd(t_process *proc)
{
	char	new_dir[100];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (shell->env[i])
	{
		if (ft_strstr(shell->env[i], "PWD=") && !ft_strstr(shell->env[i], "OLDPWD"))
			break ;
		++i;
	}
	while (shell->env[j])
	{
		if (ft_strstr(shell->env[j], "OLDPWD"))
			break ;
		++j;
	}
	if (!shell->env[i] || !shell->env[j])
		return ;
	free(shell->env[j]);
	shell->env[j] = ft_strjoin("OLDPWD=", &shell->env[i][4]);
	getcwd(new_dir, 100);
	free(shell->env[i]);
	shell->env[i] = ft_strjoin("PWD=", new_dir);
}


static void	back_to_oldpwd(t_process *proc)
{
	int	j;

	j = 0;
	while (shell->env[j])
	{
		if (ft_strstr(shell->env[j], "OLDPWD="))
			break ;
		++j;
	}
	if (!shell->env[j])
		return ;
	chdir(&shell->env[j][7]);
	if (ft_strstr(&shell->env[j][7], getenv("HOME")))
		ft_printf("~%s\n", &shell->env[j][7 + 15]);
	else
		ft_printf("%s\n", &shell->env[j][7]);
	set_pwd(proc);
}


void	print_error(char *error, char *name)
{
	write(2, error, ft_strlen(error));
	write(2, name, ft_strlen(name));
	write(2, "\n", 1);
}

int		cd_(t_process *proc)
{
	int			i;
	struct stat	buff;

	i = 1;
	proc->query[i] && !ft_strcmp(proc->query[i], "--") ? ++i : 0;
	if (proc->query[i] == NULL)
		chdir(get_home(shell->env)) != -1 ? set_pwd(proc) : 0;
	else if (!ft_strcmp(proc->query[i], "-") && proc->query[i + 1] == NULL)
		back_to_oldpwd(proc);
	else if (proc->query[i + 1] != NULL)
		print_error("cd: string not in pwd: ", proc->query[i]);
	else
	{
		if (chdir(proc->query[i]) == -1)
		{
			if (!lstat(proc->query[i], &buff) && access(proc->query[i], 0) != 0)
				print_error("cd: no such file or directory: ", proc->query[i]);
			else if ((buff.st_mode & S_IFMT) != S_IFDIR)
				print_error("cd: not a directory: ", proc->query[i]);
			else
				print_error("cd: permission denied: ", proc->query[i]);
		}
		else
			set_pwd(proc);
	}
	sh_update_cwd_info();
	return (1);
}