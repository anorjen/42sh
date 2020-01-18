/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:37:21 by sbearded          #+#    #+#             */
/*   Updated: 2019/05/20 19:50:32 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	get_cwd(char *str)
{
	char cwd[256];

	if (chdir(".") != 0)
		ft_putendl_fd("chdir() error()", 2);
	else
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			ft_putendl_fd("getcwd() error", 2);
		else
		{
			ft_strclr(str);
			ft_strcpy(str, cwd);
		}
	}
}

char	*env_path(char *key)
{
	t_vault	*ptr;

	ptr = search_key(g_env->vault, key);
	return (ptr->path);
}
