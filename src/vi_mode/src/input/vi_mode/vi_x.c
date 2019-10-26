/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_x.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 12:58:48 by anorjen           #+#    #+#             */
/*   Updated: 2019/09/28 15:38:47 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

int		vi_x(t_line *line, int count)
{
	int	pos;

	pos = line->len - line->left;
	count = (count > line->left ? line->left : count);
	if (g_strbuf)
		free(g_strbuf);
	g_strbuf = str_substr(line->str, pos, line->left);
	(line->str)[pos] = '\0';
	ft_clear_line(line->len, line->left);
	line->len -= line->left;
	line->left = 0;
	write(1, line->str, line->len);
	return (0);
}
