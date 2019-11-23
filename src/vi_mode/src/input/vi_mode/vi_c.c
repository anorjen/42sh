/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_c.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:26:02 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:26:04 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

void		ft_delline(t_line *line, int start, int size)
{
	int	i;
	int	j;
	int	pos;

	pos = line->len - line->left;
	start = (start < 0 ? 0 : start);
	size = (size > (line->len - start) ? (line->len - start) : size);
	i = start + size - 1;
	j = start;
	while (++i < line->len)
	{
		(line->str)[j] = (line->str)[i];
		++j;
	}
	(line->str)[j] = '\0';
	ft_clear_line(line->len, line->left);
	line->len -= size;
	write(1, line->str, line->len);
	if (start == pos)
		line->left = line->len - pos;
	i = 0;
	while (i < line->left)
		arrow_left(line->len, &i);
}

static void	vi_cmotion(t_line *line, int count, int key)
{
	int	pos;

	pos = line->len - line->left;
	if (key + 1000 == KC_LEFT)
		ft_delline(line, pos - count, count);
	else if (key + 1000 == KC_RIGHT)
		ft_delline(line, pos, count);
}

static void	vi_csym(t_line *line, char c)
{
	int	pos;

	pos = line->len - line->left;
	if (c == '0')
		ft_delline(line, 0, pos);
	else if (c == '^')
		ft_delline(line, 0, pos);
	else if (c == '$')
		ft_delline(line, pos, line->len);
	else if (c == 'c')
	{
		ft_clear_line(line->len, line->left);
		line->len = 0;
		line->left = 0;
		(line->str)[0] = '\0';
	}
}

int			vi_c(t_line *line, int count)
{
	char	c[6];
	int		ret;
	int		key;
	int		i;

	if ((ret = read(0, c, 6)) > 0)
	{
		if (ret == 1)
			vi_csym(line, c[0]);
		else
		{
			key = 0;
			i = -1;
			while (++i < ret)
				key += c[i];
			vi_cmotion(line, count, key);
		}
	}
	return ('i');
}

int			vi_cb(t_line *line, int count)
{
	int		pos;

	(void)count;
	pos = line->len - line->left;
	ft_delline(line, pos, line->left);
	return ('i');
}
