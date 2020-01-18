/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:57:25 by mgorczan          #+#    #+#             */
/*   Updated: 2020/01/18 20:14:13 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	check_copy_env(void)
{
	int i;

	if (!g_env_copy)
		return ;
	i = -1;
	while (g_sh->env[++i])
		ft_strdel(&(g_sh->env[i]));
	ft_memdel((void **)&(g_sh->env));
	g_sh->env = g_env_copy;
	g_env_copy = NULL;
}

t_job		*init_job(void)
{
	t_job	*new_job;

	check_copy_env();
	if ((new_job = (t_job*)malloc(sizeof(t_job))) == NULL)
		exit(1);
	new_job->pgid = -1;
	new_job->id = 0;
	new_job->mode = FOREGROUND_EXECUTION;
	return (new_job);
}

int			get_backgraund(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		++i;
	if (i > 0)
		i--;
	if (arg != NULL && arg[i] != NULL && !ft_strcmp(arg[i], "&"))
		return (BACKGROUND_EXECUTION);
	else
		return (FOREGROUND_EXECUTION);
}

t_job		*lexer(char **arg)
{
	t_job		*new_job;
	t_process	*temp_process;
	int			i;

	new_job = init_job();
	new_job->mode = get_backgraund(arg);
	i = 0;
	new_job->root = new_segment(arg, i);
	if (!new_job->root)
		return (free_job(new_job));
	while (arg[i] && ft_strcmp(arg[i], "|"))
		++i;
	i += arg[i] ? 1 : 0;
	temp_process = new_job->root;
	while (arg[i])
	{
		temp_process->next = new_segment(arg, i);
		if (!temp_process->next)
			return (free_job(new_job));
		while (arg[i] && ft_strcmp(arg[i], "|"))
			++i;
		i += arg[i] ? 1 : 0;
		temp_process = temp_process->next;
	}
	return (new_job);
}
