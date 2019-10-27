/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assist_21sh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 22:00:30 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 22:00:31 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signal)
{
	signal = 0;
	printf("\n");
}

void	sh_update_cwd_info(void)
{
	getcwd(g_sh->cur_dir, sizeof(g_sh->cur_dir));
}

char	**init_environ(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	if (!i)
		return (NULL);
	new_env = (char**)malloc(sizeof(char*) * (i + 1));
	if (!new_env)
		exit(1);
	i = -1;
	while (env[++i])
		new_env[i] = ft_strdup(env[i]);
	new_env[i] = NULL;
	return (new_env);
}
