/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_arrow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:14:26 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:14:28 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

void	arrows(int key, char **str, int *len, int *left)
{
	if (key == KC_LEFT || (key == RL_CTRL_B && g_input_mode == 2))
		arrow_left(*len, left);
	else if (key == KC_RIGHT || (key == RL_CTRL_F && g_input_mode == 2))
		arrow_right(left);
	else if (key == KC_UP || (key == RL_CTRL_P && g_input_mode == 2))
		arrow_up(str, len, left);
	else if (key == KC_DOWN || (key == RL_CTRL_N && g_input_mode == 2))
		arrow_down(str, len, left);
}

void	arrow_up(char **str, int *len, int *left)
{
	t_dlist	*buf;

	if (!g_input_line)
	{
		buf = ft_dlist_new(*str, *len);
		ft_dlist_addbegin(&g_history, buf);
		g_input_line = 1;
	}
	if (g_history && g_history->next)
	{
		ft_clear_line(*len, *left);
		g_history = g_history->next;
		write(1, g_history->content, g_history->content_size);
		*len = g_history->content_size;
		*left = 0;
		(*str)[0] = '\0';
		*str = str_addback(str, g_history->content, g_history->content_size);
		*str = str_addback(str, "\0", 1);
	}
}

void	arrow_down(char **str, int *len, int *left)
{
	if (g_history && g_history->prev)
	{
		ft_clear_line(*len, *left);
		g_history = g_history->prev;
		write(1, g_history->content, g_history->content_size);
		*len = g_history->content_size;
		*left = 0;
		(*str)[0] = '\0';
		*str = str_addback(str, g_history->content, g_history->content_size);
		*str = str_addback(str, "\0", 1);
		if (g_history->prev == NULL && g_input_line == 1)
		{
			ft_dlist_delone(&g_history);
			g_input_line = 0;
		}
	}
}

void	arrow_left(int len, int *left)
{
	if (*left < len)
	{
		tputs(g_term->le, 1, ft_put);
		(*left)++;
	}
}

void	arrow_right(int *left)
{
	if (*left > 0)
	{
		tputs(g_term->nd, 1, ft_put);
		(*left)--;
	}
}
