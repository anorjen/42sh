/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_f.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:26:45 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 21:26:46 by sbearded         ###   ########.fr       */
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
