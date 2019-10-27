/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_l.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:24:35 by anorjen           #+#    #+#             */
/*   Updated: 2019/09/28 15:38:57 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

int	vi_l(t_line *line, int count)
{
	count = (count > line->left ? line->left : count);
	while (count--)
		arrow_right(&(line->left));
	return (0);
}
