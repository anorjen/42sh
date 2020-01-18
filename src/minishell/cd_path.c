/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:41:29 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/11/28 20:37:50 by yharwyn-         ###   ########.fr       */
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

void		set_pwd(char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len != 1 && path[len - 1] == '/')
		cut_str(&path, len - 1, len);
	set_env("OLDPWD", get_env("PWD"));
	set_env("PWD", path);
	sh_update_cwd_info();
	free(path);
}
