/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_segment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:57:37 by mgorczan          #+#    #+#             */
/*   Updated: 2019/11/23 18:08:56 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int			get_command_type_(char *command)
{
	if (ft_strequ(command, "exit")
		|| ft_strequ(command, "cd")
		|| ft_strequ(command, "setenv")
		|| ft_strequ(command, "unsetenv")
		|| ft_strequ(command, "jobs")
		|| ft_strequ(command, "bg")
		|| ft_strequ(command, "fg")
		|| ft_strequ(command, "kill")
		|| ft_strequ(command, "alias")
		|| ft_strequ(command, "unalias")
		|| ft_strequ(command, "set")
		|| ft_strequ(command, "unset")
		|| ft_strequ(command, "export")
		|| ft_strequ(command, "fc")
		|| ft_strequ(command, "echo"))
		return (1);
	else
		return (COMMAND_EXTERNAL);
}

t_process	*init_process(void)
{
	t_process	*new_process;

	if ((new_process = (t_process*)malloc(sizeof(t_process))) == NULL)
		exit(1);
	new_process->query = NULL;
	new_process->output_file = NULL;
	new_process->output_path = NULL;
	new_process->output_mode = 0;
	new_process->heredoc = NULL;
	new_process->input_path = NULL;
	new_process->input_file = NULL;
	new_process->aggregate = NULL;
	new_process->pid = -1;
	new_process->type = 0;
	new_process->status = 0;
	new_process->next = NULL;
	new_process->out_fdPIPE = 1;
	return (new_process);
}

t_process	*new_segment(char **arg, int i)
{
	t_process	*new_process;

	new_process = init_process();
	new_process->query = new_query(arg, i);
	if (!new_process->query)
	{
		free(new_process);
		return (NULL);
	}
	new_process->type = get_command_type_(new_process->query[0]);
	new_process->exec_mode = 1;
	input_path(arg, i, new_process);
	output_path(arg, i, new_process);
	new_agregation(arg, i, new_process);
	return (new_process);
}
