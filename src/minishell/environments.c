/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environments.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 16:33:16 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/26 17:46:11 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	print_env(t_process *proc)
{
	int i;

	i = 0;
	proc = NULL;
	while (shell->env && shell->env[i])
		ft_printf("%s\n", shell->env[i++]);
	return (1);
}


char	*new_env(t_process *proc)
{
	char	*new_env;
	char	*temp;

	new_env = NULL;
	if (proc->query[1] == NULL)
		write(2, "setenv: not enough arguments\n", 29);
	if (!ft_strcmp(proc->query[1], "="))
		write(2, "zsh: bad assignment\n", 20);
	if (proc->query[2] == NULL)
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

int	setenv_(t_process *proc)
{
	int		i;
	int		j;
	char	**temp;
	char	*tm;

	i = -1;
	if ((tm = new_env(proc)) == NULL)
		exit (1);
	while (shell->env[++i])
	{
		j = 0;
		while (shell->env[i][j] == tm[j] && tm[j] != '=')
			++j;
		if (shell->env[i][j] == tm[j])
			CHANGE_ENV;
	}
	j = -1;
	if ((temp = (char**)malloc(sizeof(char*) * (i + 2))) == NULL)
		exit(1);
	temp[i + 1] = NULL;
	while (++j < i)
		temp[j] = shell->env[j];
	temp[j] = tm;
	free(shell->env);
	shell->env = temp;
	return (1);
}

int		remove_env(t_process *proc)
{
	int		i;
	int		j;
	int		k;
	int		count;

	i = -1;
	count = 0;
	while (shell->env[++i])
	{
		j = 0;
		while (proc->query[++j])
		{
			k = 0;
			while (shell->env[i][k] != '='
				   && proc->query[j][k] == shell->env[i][k])
				++k;
			if (shell->env[i][k] == '=')
			{
				free(shell->env[i]);
				shell->env[i] = ft_strdup("\0");
				++count;
			}
		}
	}
	return (i - count);
}

int	unset_(t_process *proc)
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
	if ((temp = (char**)malloc(sizeof(char*) * (count + 1))) == NULL)
		exit(1);
	j = 0;
	k = -1;
	while (shell->env[++k])
	{
		if (shell->env[k][0] != '\0')
			temp[j++] = shell->env[k];
		else
			free(shell->env[k]);
	}
	temp[j] = NULL;
	free(shell->env);
	shell->env = temp;
	return (1);
}


char	*get_env(char *varible, char **environ)
{
	int	i;
	int	j;

	i = 0;
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
	return (NULL);
}


char	*get_home(char **environ)
{
	char	*path;
	char	*temp;
	int		i;

	i = 0;
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
		if (ft_strstr(shell->env[i], "PWD"))
			break ;
		++i;
	}
	while (shell->env[j])
	{
		if (ft_strstr(shell->env[j], "OLDPWD"))
			break ;
		++j;
	}
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
		if (get_env("OLDPWD", shell->env))
			break ;
		++j;
	}
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