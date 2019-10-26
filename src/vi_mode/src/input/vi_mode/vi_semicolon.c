/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_semicolon.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 19:01:16 by anorjen           #+#    #+#             */
/*   Updated: 2019/09/28 15:38:51 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

int		vi_semicolon(t_line *line, int count)
{
	if (g_vi_last[0] == 'f')
		vi_f_do(line, count, g_vi_last[1]);
	else if (g_vi_last[0] == 'F')
		vi_fb_do(line, count, g_vi_last[1]);
	return (0);
}
