/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_query.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 20:49:40 by mgorczan          #+#    #+#             */
/*   Updated: 2019/12/14 13:50:18 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		get_mode(char *command)
{
	if (strcmp(command, "|") == 0)
		return (COMMAND_PIPE);
	else if (strcmp(command, "<") == 0 || (ft_isdigit(command[0]) &&
		strcmp(&command[1], "<") == 0))
		return (COMMAND_LREDIR);
	else if (strcmp(command, ">") == 0 || (ft_isdigit(command[0]) &&
		strcmp(&command[1], ">") == 0))
		return (COMMAND_RREDIR);
	else if ((ft_isdigit(command[0]) && strcmp(&command[1], ">&") == 0) ||
		strcmp(command, ">&") == 0)
		return (COMMAND_ARG);
	else if ((ft_isdigit(command[0]) && strcmp(&command[1], "<&") == 0) ||
		strcmp(command, "<&") == 0)
		return (COMMAND_ARG);
	else if (strcmp(command, "<<") == 0)
		return (COMMAND_HEREDOC);
	else if (strcmp(command, ">>") == 0)
		return (COMMAND_APPEND);
	else if (strcmp(command, "&") == 0)
		return (COMMAND_BACKGR);
	else if (ft_isdigit(command[0]) && command[1] == '>' && command[2] == '&')
		return (1);
	else if (ft_isdigit(command[0]) && command[1] == '<' && command[2] == '&')
		return (1);
	return (COMMAND_EXTERNAL);
}

int		lenght_argproc(char **arg, int i)
{
	int lenght;

	lenght = 0;
	while (arg[i] && ft_strcmp(arg[i], "|"))
	{
		if (get_mode(arg[i]))
			++i;
		else
			++lenght;
		arg[i] ? ++i : 0;
	}
	return (lenght);
}

char	**new_query(char **arg, int i)
{
	char	**query;
	int		lenght;
	int		j;

	j = 0;
	if ((lenght = lenght_argproc(arg, i)) == 0)
		return (NULL);
	if ((query = malloc(sizeof(char*) * (lenght + 1))) == NULL)
		exit(1);
	while (j < lenght)
	{
		if (get_mode(arg[i]))
			i += 1;
		else
		{
			query[j] = ft_strdup(arg[i]);
			++j;
		}
		if (!arg[i++])
			break ;
	}
	query[j] = NULL;
	return (query);
}
