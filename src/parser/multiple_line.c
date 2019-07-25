/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:21:05 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/25 17:21:06 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"


int which_specdel(char *line, int i)
{
	if (!line)
		return (0);
	if (line[i] == '|' && line[i + 1] == '|')
		return (MODE_OR);
	else if (line[i] == '|')
		return (MODE_PIPE);
	else if (line[i] == '&' && line[i + 1] == '&')
		return (MODE_AND);
	else if (line[i] == '&')
		return (MODE_BACKGROUND);
	return (0);
}


int						multiply_line(char *line)
{
	int     i;
	int		mode;
	char    quote;

	i = 0;
	mode = 0;
	while (line && line[i])
	{
		if ((line[i] == '\"' || line[i] == '\'') && !(i > 0 && line[i - 1] == '\\'))
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				++i;
			if  (!line[i++])
				return (MODE_QUOTE);
		}
		else if (is_specdel(line, i))
		{
			mode = which_specdel(line, i);
			i += is_specdel(line, i);
			while (line[i] && is_delim(line[i]))
				++i;
			if (!line[i])
				return (mode);
		}
		else
			++i;
	}
	// if (i > 0 && line[i - 1] == '\\')
	// 	return (MODE_MULTILINE);
	return (0);
}
