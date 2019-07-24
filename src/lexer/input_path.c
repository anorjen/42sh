/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 20:50:04 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/23 20:50:05 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	lenght_argher(char **arg, int i)
{
	int	lenght;

	lenght = 0;
	while (arg[i] && ft_strcmp(arg[i], "|"))
		if (!ft_strcmp(arg[i++], "<<"))
			lenght++;
	return (lenght);
}

static int	lenght_argre(char **arg, int i)
{
	int lenght;

	lenght = 0;
	while (arg[i] && ft_strcmp(arg[i], "|"))
		if (!ft_strcmp(arg[i++], "<"))
			lenght++;
	return (lenght);
}

static void	fill_input(char **arg, int i, t_process *new_process)
{
	int j;
	int k;

	j = 0;
	k = 0;
	while (arg[i] && ft_strcmp(arg[i], "|"))
	{
		if (!ft_strcmp(arg[i], "<<"))
		{
			new_process->heredoc[j++] = ft_strdup(arg[i + 1]);
			if (new_process->input_path)
				free(new_process->input_path);
			new_process->input_path = NULL;
		}
		if (!ft_strcmp(arg[i], "<"))
		{
			new_process->input_file[k] = ft_strdup(arg[i + 1]);
			if (new_process->input_path)
				free(new_process->input_path);
			new_process->input_path = ft_strdup(new_process->input_file[k++]);
		}
		++i;
	}
}

void		input_path(char **arg, int i, t_process *new_process)
{
	int lenght_he;
	int lenght_re;

	lenght_he = lenght_argher(arg, i);
	lenght_re = lenght_argre(arg, i);
	if (lenght_he)
	{
		new_process->heredoc = (char**)malloc(sizeof(char*) * (lenght_he + 1));
		!new_process->heredoc ? exit(1) : 0;
		new_process->heredoc[lenght_he] = NULL;
	}
	if (lenght_re)
	{
		new_process->input_file = (char**)malloc(sizeof(char*) *
														(lenght_re + 1));
		!new_process->input_file ? exit(1) : 0;
		new_process->input_file[lenght_re] = NULL;
	}
	fill_input(arg, i, new_process);
}
