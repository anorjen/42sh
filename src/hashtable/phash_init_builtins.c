/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phash_init_builtins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 13:21:17 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/05 16:01:37 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/hashtable.h"

const char	*g_builtin_str[] = {
	"cd",
	"help",
	"exit",
	"echo",
	"jobs",
	"bg",
	"fg",
	"kill",
	"env",
	"setenv",
	"unsetenv",
	"type"
};

int			(*g_builtin_func[]) (t_process *) = {
	&cd_,
	&help_shell,
	&exit_shell,
	&echo,
	&shell_jobs,
	&shell_bg,
	&shell_fg,
	&shell_kill,
	&print_env,
	&setenv_,
	&unset_,
	NULL
};

void		phash_init_builtins(void)
{
	int	i;

	i = -1;
	while (++i < NUM_BUILTINS)
		hash_insert(ft_strdup(g_builtin_str[i]), g_hash_built,
					g_builtin_func[i]);
}
