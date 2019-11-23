/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_comma.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:26:10 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:26:11 by mgorczan         ###   ########.fr       */
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
