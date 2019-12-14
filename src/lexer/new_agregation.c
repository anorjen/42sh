/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_agregation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 20:57:55 by mgorczan          #+#    #+#             */
/*   Updated: 2019/12/14 14:04:36 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		is_agrarg(char *command)
{
	if (ft_isdigit(command[0]) && command[1] == '>'  && command[2] == '&')
		return (1);
	else if (ft_isdigit(command[0]) && command[1] == '<'  && command[2] == '&')
		return (1);
	return (0);
}

int		lenght_agrg(char **arg, int i)
{
	int lenght;

	lenght = 0;
	while (arg[i] && ft_strcmp(arg[i], "|"))
	{
		if (is_agrarg(arg[i]) && ft_isdigit(arg[i + 1][0]))
			++lenght;
		++i;
	}
	return (lenght);
}

void	new_agregation(char **arg, int i, t_process *new_process)
{
	int lenght;

	lenght = lenght_agrg(arg, i);
	ft_printf("%i\n", lenght);
	if (lenght == 0)
		return ;
	new_process->aggregate = (t_aggregation*)malloc(sizeof(t_aggregation));
	if (new_process->aggregate == NULL)
		exit(1);
	while (arg[i] && ft_strcmp(arg[i], "|"))
	{
		if (is_agrarg(arg[i]) && ft_isdigit(arg[i + 1][0]))
		{
			new_process->aggregate->in = arg[i][0] - 48;
			if (!ft_strcmp(arg[i + 1], "-"))
				new_process->aggregate->out = -1;
			else
				new_process->aggregate->out = ft_atoi(arg[i + 1]);
		}
		++i;
	}
}
