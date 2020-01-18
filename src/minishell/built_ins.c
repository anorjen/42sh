/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:56:08 by sbearded          #+#    #+#             */
/*   Updated: 2019/12/03 15:27:16 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern const char	*g_builtin_str[];

int					help_shell(t_process *proc)
{
	int		i;

	proc = NULL;
	ft_printf("21shell of 21's school project\n");
	ft_printf("Built-in commands (input argument if needed):\n");
	i = 0;
	while (i < NR_BUILTINS)
	{
		ft_printf("\t -> %s\n", g_builtin_str[i]);
		i++;
	}
	ft_printf("For additional info -> use \"man\".\n");
	return (1);
}

int					check_numeric(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
	}
	return (0);
}

int					exit_shell(t_process *proc)
{
	int		i;

	i = 0;
	if (proc->query[1] && proc->query[2])
	{
		print_error("exit: too many arguments", "");
		return (1);
	}
	if (proc->query[1])
	{
		if (check_numeric(proc->query[1]))
		{
			print_error("exit: numeric argument required", "");
			return (1);
		}
		i = ft_atoi(proc->query[1]);
	}
	if (i == -1)
		i = 255;
	else if (i > 255)
		i %= 256;
	ft_printf(COLOR_MAGENTA "say-o-nara~\n" COLOR_NONE);
	save_history();
	shell_cleaner();
	exit(i);
}

int					echo(t_process *proc)
{
	int		i;

	i = 1;
	while (proc->query[i] != 0)
	{
		ft_printf("%s", proc->query[i]);
		i++;
		if (proc->query[i])
			ft_printf(" ");
	}
	ft_printf("\n");
	return (0);
}

void				shell_cleaner(void)
{
	int		i;

	i = 0;
	if (g_sh->jobs[i])
	{
		while (g_sh->jobs[i])
			free_job(g_sh->jobs[i++]);
	}
	free_arg(g_sh->env);
	alias_deinit();
	phash_deinit();
	set_deinit();
	if (g_search_word)
		free(g_search_word);
}
