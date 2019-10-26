/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_segment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:13:28 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/05 15:41:03 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int			get_command_type_(char *command)
{
	if (ft_strequ(command, "exit")
		|| ft_strequ(command, "cd")
		|| ft_strequ(command, "setenv")
		|| ft_strequ(command, "unsetenv"))
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
