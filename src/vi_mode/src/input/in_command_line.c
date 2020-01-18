/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_command_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:14:38 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 21:14:40 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

int				is_arrow(int key)
{
	if ((key >= KC_UP && key <= KC_LEFT) ||
		(g_input_mode == 2 && (key == RL_CTRL_B || key == RL_CTRL_F
			|| key == RL_CTRL_P || key == RL_CTRL_N)))
		return (1);
	return (0);
}

void			ft_backspace(char **str, int *len, int left)
{
	int			pos;
	char		*buf;

	pos = *len - left;
	if (pos > 0)
	{
		tputs(g_term->le, 1, ft_put);
		tputs(g_term->dc, 1, ft_put);
		buf = str_substr(*str, pos, left);
		(*str)[pos - 1] = '\0';
		(*str)[*len - 1] = '\0';
		*str = str_addback(str, buf, left);
		(*len)--;
	}
}

void			ft_delkey(char **str, int *len, int *left)
{
	int			pos;
	char		*buf;

	pos = *len - *left;
	if (pos > 0 && pos < *len)
	{
		tputs(g_term->dc, 1, ft_put);
		buf = str_substr(*str, pos + 1, *left - 1);
		(*str)[pos] = '\0';
		(*str)[*len - 1] = '\0';
		*str = str_addback(str, buf, *left - 1);
		(*len)--;
		(*left)--;
	}
}

void			ft_clear_line(int len, int left)
{
	int		pos;

	pos = len - left + 1;
	while (--pos)
		tputs(g_term->le, 1, ft_put);
	tputs(g_term->cd, 1, ft_put);
}

void			ft_newline(t_line *line)
{
	t_dlist	*elem;

	if (g_input_line)
	{
		g_history = ft_dlist_rewind(g_history);
		ft_dlist_delone(&g_history);
		g_input_line = 0;
	}
	write(1, "\n", 1);
	if (is_str(line->str))
	{
		ft_quotes(line);
		elem = ft_dlist_new(line->str, line->len);
		ft_dlist_addbegin(&g_history, elem);
	}
}
