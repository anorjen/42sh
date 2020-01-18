/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_ft_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:15:07 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 21:15:09 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

static void	ft_qpromt(char q)
{
	if (q == '\'')
		write(1, "quote> ", 7);
	else if (q == '"')
		write(1, "dquote> ", 8);
	else if (q == '`')
		write(1, "bquote> ", 8);
	else if (q == '\\' || is_open_bracket(q))
		write(1, "> ", 2);
	else if (q == '|')
		write(1, "pipe> ", 6);
}

int			is_quote(char c)
{
	if (c == '\'' || c == '"' || c == '`')
		return (1);
	return (0);
}

int			is_backslash(char *str, int i)
{
	int	slash;

	slash = 0;
	while (i > 0 && str[--i] == '\\')
		++slash;
	if (slash % 2 != 0)
		return (1);
	return (0);
}

static char	ft_find_quote(char *str)
{
	int		i;
	char	q;

	q = 0;
	i = -1;
	while (str[++i])
	{
		if (q != 0 && str[i] == q && !is_backslash(str, i))
			q = 0;
		else if (((i > 0 && !is_backslash(str, i) && is_quote(str[i]))
			|| (i == 0 && is_quote(str[i]))) && q == 0)
			q = str[i];
	}
	if (!q && i > 0)
	{
		if (str[i - 1] == '|')
		{
			q = '|';
			--i;
		}
		if (is_backslash(str, i))
			q = (q == 0 ? '\\' : 0);
	}
	return (q);
}

void		ft_quotes(t_line *line)
{
	int		key;
	t_line	*tmp;
	char	q;

	q = ft_find_quote(line->str);
	q = (q == 0 ? ft_find_bracket(line->str) : q);
	if (q && (tmp = line_init()))
	{
		ft_qpromt(q);
		while (1)
		{
			key = ft_read_keycode(1, tmp);
			if (key == KC_NL)
			{
				if (!(q == '\\' && tmp->len == 0))
				{
					line->str = str_addback(&(line->str), tmp->str, tmp->len);
					line_deinit(tmp);
					ft_newline(line);
				}
				break ;
			}
			keycode_func(key, tmp);
		}
	}
}
