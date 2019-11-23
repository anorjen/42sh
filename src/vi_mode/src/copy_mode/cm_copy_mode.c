/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cm_copy_mode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:12:25 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:12:28 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

static void	cm_left(char *line, int len, int *left, int *start_pos)
{
	if (*left < len)
	{
		tputs(g_term->le, 1, ft_put);
		(*left)++;
		write(1, &line[len - *left], 1);
		tputs(g_term->le, 1, ft_put);
	}
	(*start_pos)--;
}

static void	cm_right(char *line, int len, int *left)
{
	tputs(g_term->so, 1, ft_put);
	if (*left > 0)
	{
		write(1, &line[len - *left], 1);
		(*left)--;
	}
	tputs(g_term->se, 1, ft_put);
}

void		ft_copy_mode(t_line *line)
{
	int			key;
	int			start_pos;

	start_pos = line->len - line->left;
	while (1)
	{
		key = ft_read_keycode(0, line);
		if (key == KC_LEFT)
			cm_left(line->str, line->len, &(line->left), &start_pos);
		else if (key == KC_RIGHT)
			cm_right(line->str, line->len, &(line->left));
		else if (key == KC_COPY)
			g_strbuf = ft_copy(line->str, start_pos, line->len - line->left);
		else if (key == KC_PASTE && g_strbuf)
			ft_paste(&(line->str), &(line->len), &(line->left), g_strbuf);
		else if (key == KC_CUT)
			g_strbuf = ft_cut(&(line->str), start_pos, &(line->len),
															&(line->left));
		else if (key == KC_ESC || key == 'Q' || key == 'q')
			break ;
	}
}
