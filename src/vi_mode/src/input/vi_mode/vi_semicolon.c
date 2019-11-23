/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_semicolon.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:28:47 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:28:48 by mgorczan         ###   ########.fr       */
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
