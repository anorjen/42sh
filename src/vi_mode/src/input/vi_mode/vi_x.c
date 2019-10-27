/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_x.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:29:14 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:29:15 by mgorczan         ###   ########.fr       */
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
