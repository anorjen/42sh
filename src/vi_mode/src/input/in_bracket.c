/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_bracket.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:14:32 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:14:34 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

int			is_open_bracket(char c)
{
	if (c == '(' || c == '[' || c == '{')
		return (1);
	return (0);
}

int			is_close_bracket(char open_bracket, char c)
{
	char	close_bracket;

	close_bracket = 0;
	if (open_bracket == '(')
		close_bracket = ')';
	else if (open_bracket == '[')
		close_bracket = ']';
	else if (open_bracket == '{')
		close_bracket = '}';
	if (c == close_bracket)
		return (1);
	return (0);
}

int			find_close_quote(char *str, int i, char quote)
{
	while (str[++i])
	{
		if ((i > 0 && str[i] == quote && !is_backslash(str, i))
		|| (i == 0 && str[i] == quote))
			return (i);
	}
	return (-1);
}

char		ft_find_bracket(char *str)
{
	int		i;
	char	bracket;

	bracket = 0;
	i = -1;
	while (str[++i])
	{
		if (((i > 0 && !is_backslash(str, i) && is_quote(str[i]))
			|| (i == 0 && is_quote(str[i]))))
		{
			i = find_close_quote(str, i, str[i]);
			if (i == -1)
				return (0);
		}
		if (bracket != 0 && is_close_bracket(bracket, str[i])
										&& !is_backslash(str, i))
			bracket = 0;
		else if (((i > 0 && !is_backslash(str, i) && is_open_bracket(str[i]))
			|| (i == 0 && is_open_bracket(str[i]))) && bracket == 0)
			bracket = str[i];
	}
	return (bracket);
}
