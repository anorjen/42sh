/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phash_init_builtins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:44:26 by mgorczan          #+#    #+#             */
/*   Updated: 2019/11/23 18:13:49 by yharwyn-         ###   ########.fr       */
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

int			echo_(t_process *proc)
{
	int i;
	int	n;

	i = 1;
	n = 0;
	if (proc->query[1] == NULL)
	{
		write(proc->out_fdPIPE, "\n", 1);
		return (1);
	}
	while (proc->query[i] &&
		   (!ft_strcmp(proc->query[i], "-n")
			|| !ft_strcmp(proc->query[i], "-e")))
		n = !ft_strcmp(proc->query[i++], "-n") ? 1 : 0;
	if (proc->query[i] &&
		!ft_strcmp(proc->query[i], "-"))
		++i;
	if (!proc->query[i] && n)
		return (1);
	while (proc->query[i])
	{
		write(proc->out_fdPIPE, proc->query[i], ft_strlen(proc->query[i]));
		proc->query[++i] ? write(proc->out_fdPIPE, " ", 1) : 0;
	}
	write(proc->out_fdPIPE, "\n", 1);
	return (1);

}

int			(*g_builtin_func[]) (t_process *) = {
	&cd_,
	&help_shell,
	&exit_shell,
	&echo_,
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
