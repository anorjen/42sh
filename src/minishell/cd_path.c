/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:41:29 by sbearded          #+#    #+#             */
/*   Updated: 2019/11/19 20:00:44 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			cd_ext(char *path)
{
	struct stat buff;

	if (!lstat(path, &buff) && access(path, 0) != 0)
		print_error("cd: no such file or directory: ", path);
	else if ((buff.st_mode & S_IFMT) != S_IFDIR)
		print_error("cd: not a directory: ", path);
	else
		print_error("cd: permission denied: ", path);
	return (1);
}

void		set_pwd(char *path, int flag)
{
	char	new_dir[100];

	set_env("OLDPWD", get_env("PWD"));
	if (flag == CD_P_FLAG)
		set_env("PWD", getcwd(new_dir, 100));
	else
		set_env("PWD", path);
}

int			cd_path(char *path, int flag)
{
	char	*abs_path;

	abs_path = path;
	if (chdir(abs_path) == -1)
	{
		cd_ext(path);
		return (1);
	}
	set_pwd(path, flag);
	return (0);
	//if (chdir(dir) == -1)
//		return (cd_ext(dir));
}
