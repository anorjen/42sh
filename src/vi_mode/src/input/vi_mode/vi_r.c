/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_r.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 19:14:00 by anorjen           #+#    #+#             */
/*   Updated: 2019/09/28 15:38:55 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

int		vi_r(t_line *line, int count)
{
	int		ret;
	char	c;
	int		i;
	int		pos;

	if ((ret = read(0, &c, 1)) == 1)
	{
		pos = line->len - line->left;
		count = (count > line->left ? line->left : count);
		i = -1;
		while (++i < count)
		{
			(line->str)[pos + i] = c;
			write(1, &c, 1);
		}
		line->left -= count;
	}
	return (0);
}
