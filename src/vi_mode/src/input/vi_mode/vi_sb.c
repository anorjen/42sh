/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_sb.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 12:50:43 by anorjen           #+#    #+#             */
/*   Updated: 2019/09/28 15:38:53 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

int		vi_sb(t_line *line, int count)
{
	++count;
	ft_clear_line(line->len, line->left);
	(line->str)[0] = '\0';
	line->len = 0;
	line->left = 0;
	return ('i');
}
