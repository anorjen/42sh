/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_comma.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 19:12:47 by anorjen           #+#    #+#             */
/*   Updated: 2019/09/28 15:39:50 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

int		vi_comma(t_line *line, int count)
{
	if (g_vi_last[0] == 'f')
		vi_fb_do(line, count, g_vi_last[1]);
	else if (g_vi_last[0] == 'F')
		vi_f_do(line, count, g_vi_last[1]);
	return (0);
}
