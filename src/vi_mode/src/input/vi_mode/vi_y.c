/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_y.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:29:25 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:29:26 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

static void	vi_ymotion(t_line *line, int count, int key)
{
	int	pos;
	int	start;

	start = 0;
	pos = line->len - line->left;
	if (key + 1000 == KC_LEFT)
		start = pos - count;
	else if (key + 1000 == KC_RIGHT)
		start = pos;
	if (g_strbuf)
		free(g_strbuf);
	g_strbuf = str_substr(line->str, start, count);
}

static void	vi_ysym(t_line *line, char c)
{
	int	pos;
	int	start;
	int	size;

	start = 0;
	size = 0;
	pos = line->len - line->left;
	if (c == '0' || c == '^')
	{
		start = 0;
		size = pos;
	}
	else if (c == '$')
	{
		start = pos;
		size = line->left;
	}
	else if (c == 'c')
	{
		start = 0;
		size = line->len;
	}
	if (g_strbuf)
		free(g_strbuf);
	g_strbuf = str_substr(line->str, start, size);
}

int			vi_y(t_line *line, int count)
{
	char	c[6];
	int		ret;
	int		key;
	int		i;

	if ((ret = read(0, c, 6)) > 0)
	{
		if (ret == 1)
			vi_ysym(line, c[0]);
		else
		{
			key = 0;
			i = -1;
			while (++i < ret)
				key += c[i];
			vi_ymotion(line, count, key);
		}
	}
	return ('i');
}

int			vi_yb(t_line *line, int count)
{
	int		pos;

	(void)count;
	pos = line->len - line->left;
	if (g_strbuf)
		free(g_strbuf);
	g_strbuf = str_substr(line->str, pos, line->len);
	return ('i');
}
