/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_d.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 18:53:15 by anorjen           #+#    #+#             */
/*   Updated: 2019/09/28 17:44:58 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

static void	vi_dmotion(t_line *line, int count, int key)
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
	ft_delline(line, start, count);
}

static void	vi_dsym(t_line *line, char c)
{
	int	pos;
	int	start;
	int	size;

	start = 0;
	size = 0;
	pos = line->len - line->left;
	if (c == '0' || c == '^')
		size = pos;
	else if (c == '$')
	{
		start = pos;
		size = line->left;
	}
	else if (c == 'c')
		size = line->len;
	if (g_strbuf)
		free(g_strbuf);
	g_strbuf = str_substr(line->str, start, size);
	ft_delline(line, start, size);
}

int			vi_d(t_line *line, int count)
{
	char	c[6];
	int		ret;
	int		key;
	int		i;

	if ((ret = read(0, c, 6)) > 0)
	{
		if (ret == 1)
			vi_dsym(line, c[0]);
		else
		{
			key = 0;
			i = -1;
			while (++i < ret)
				key += c[i];
			vi_dmotion(line, count, key);
		}
	}
	return ('i');
}

int			vi_db(t_line *line, int count)
{
	int		pos;

	(void)count;
	pos = line->len - line->left;
	if (g_strbuf)
		free(g_strbuf);
	g_strbuf = str_substr(line->str, pos, line->len - pos);
	ft_delline(line, pos, line->len);
	return ('i');
}
