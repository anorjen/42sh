/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_h.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 17:48:29 by anorjen           #+#    #+#             */
/*   Updated: 2019/09/28 15:39:40 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

int	vi_h(t_line *line, int count)
{
	int		pos;

	pos = line->len - line->left;
	count = (count > pos ? pos : count);
	while (count--)
		arrow_left(line->len, &(line->left));
	return (0);
}
