/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_f.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 18:30:47 by anorjen           #+#    #+#             */
/*   Updated: 2019/09/28 15:39:45 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

static void	find_char(t_line *line, char c)
{
	int	i;
	int	pos;

	pos = line->len - line->left;
	i = pos;
	while ((line->str)[i] && (line->str)[i] != c)
		++i;
	if ((line->str)[i] == c)
	{
		while (i > pos)
		{
			arrow_right(&(line->left));
			--i;
		}
	}
}

void		vi_f_do(t_line *line, int count, char c)
{
	int	pos;

	pos = line->len - line->left;
	while (count-- && pos < line->len)
		find_char(line, c);
}

int			vi_f(t_line *line, int count)
{
	int		ret;
	char	c;

	if ((ret = read(0, &c, 1)) == 1)
	{
		vi_f_do(line, count, c);
		g_vi_last[0] = 'f';
		g_vi_last[1] = c;
	}
	return (0);
}
