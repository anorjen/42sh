/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_r.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:28:27 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:28:28 by mgorczan         ###   ########.fr       */
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
