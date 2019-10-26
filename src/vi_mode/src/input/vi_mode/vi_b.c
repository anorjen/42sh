/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_b.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 17:59:56 by anorjen           #+#    #+#             */
/*   Updated: 2019/09/28 15:39:54 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

int	vi_b(t_line *line, int count)
{
	int		pos;

	pos = line->len - line->left;
	while (count-- && pos > 0)
	{
		ft_key_prev(line->str, line->len, &(line->left));
		pos = line->len - line->left;
	}
	return (0);
}
