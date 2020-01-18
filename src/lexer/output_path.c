/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 21:00:00 by mgorczan          #+#    #+#             */
/*   Updated: 2019/12/14 13:20:08 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		lenght_outpth(char **arg, int i)
{
	int lenght;

	lenght = 0;
	while (arg[i] && ft_strcmp(arg[i], "|"))
	{
		if (!ft_strcmp(arg[i], ">") || !ft_strcmp(arg[i], ">>")
			|| !ft_strcmp(arg[i], ">&"))
			lenght++;
		++i;
	}
	return (lenght);
}

void	fill_outputline(char **arg, int i, t_process *new_process)
{
	int j;

	j = 0;
	while (arg[i] && ft_strcmp(arg[i], "|"))
	{
		if (!ft_strcmp(arg[i], ">") || !ft_strcmp(arg[i], ">&"))
		{
			new_process->is_output_fd[j] = !ft_strcmp(arg[i], ">&")
					? IS_OUTPUT_FD : 0;
			new_process->output_file[j++] = ft_strdup(arg[i + 1]);
			new_process->output_mode = 1;
			if (new_process->output_path)
				free(new_process->output_path);
			new_process->output_path = ft_strdup(arg[i + 1]);
		}
		else if (!ft_strcmp(arg[i], ">>"))
		{
			new_process->output_file[j++] = ft_strdup(arg[i + 1]);
			new_process->output_mode = 2;
			if (new_process->output_path)
				free(new_process->output_path);
			new_process->output_path = ft_strdup(arg[i + 1]);
		}
		++i;
	}
	new_process->output_file[j] = NULL;
}

void	output_path(char **arg, int i, t_process *new_process)
{
	int lenght;

	lenght = lenght_outpth(arg, i);
	if (!lenght)
		return ;
	new_process->output_file = (char**)malloc(sizeof(char*) * (lenght + 1));
	new_process->is_output_fd = (int*)malloc(sizeof(int) * (lenght));
	if (new_process->output_file == NULL || new_process->is_output_fd == NULL)
		exit(1);
	fill_outputline(arg, i, new_process);
}
