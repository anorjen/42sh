/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:17:53 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:17:56 by mgorczan         ###   ########.fr       */
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
