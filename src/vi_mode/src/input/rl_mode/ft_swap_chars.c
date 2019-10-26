/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 18:04:13 by anorjen           #+#    #+#             */
/*   Updated: 2019/09/28 15:40:02 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

void	ft_swap_chars(t_line *line)
{
	int		pos;
	char	buf;

	if (line->left == 0)
		arrow_left(line->len, &(line->left));
	pos = line->len - line->left;
	if (pos > 0)
	{
		buf = (line->str)[pos];
		(line->str)[pos] = (line->str)[pos - 1];
		(line->str)[pos - 1] = buf;
		arrow_left(line->len, &(line->left));
		write(1, &(line->str)[pos - 1], 2);
		line->left -= 2;
	}
}
