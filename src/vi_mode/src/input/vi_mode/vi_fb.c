/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_fb.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:26:51 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 21:26:53 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

static void	find_char(t_line *line, char c)
{
	int	i;
	int	pos;

	pos = line->len - line->left;
	i = pos;
	while (i > 0 && (line->str)[i] != c)
		--i;
	if ((line->str)[i] == c)
	{
		while (i < pos)
		{
			arrow_left(line->len, &(line->left));
			++i;
		}
	}
}

void		vi_fb_do(t_line *line, int count, char c)
{
	int	pos;

	pos = line->len - line->left;
	while (count-- && pos >= 0)
		find_char(line, c);
}

int			vi_fb(t_line *line, int count)
{
	int		ret;
	char	c;

	if ((ret = read(0, &c, 1)) == 1)
	{
		vi_fb_do(line, count, c);
		g_vi_last[0] = 'F';
		g_vi_last[1] = c;
	}
	return (0);
}
