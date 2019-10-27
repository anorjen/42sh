/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phash_init_builtins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 13:21:17 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 11:24:45 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

const char	*g_builtin_str[] = {
	"cd",
	"help",
	"exit",
	"echo",
	"jobs",
	"bg",
	"fg",
	"kill",
	"type",
	"alias",
	"unalias",
	"env",
	"setenv",
	"unsetenv",
	"set",
	"unset",
	"export",
	"fc",
	NULL
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
	&type_shell,
	&ms_alias,
	&ms_unalias,
	&print_env,
	&setenv_,
	&unset_,
	&ms_set,
	&ms_unset,
	&ms_export,
	&shell_fc,
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
