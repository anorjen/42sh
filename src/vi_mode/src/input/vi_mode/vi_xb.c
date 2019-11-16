/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_xb.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:29:19 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:29:20 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

int		vi_xb(t_line *line, int count)
{
	int		pos;
	int		i;

	pos = line->len - line->left;
	count = (count > pos ? pos : count);
	if (g_strbuf)
		free(g_strbuf);
	g_strbuf = str_substr(line->str, pos - count, count);
	i = -1;
	while (++i < line->left)
		line->str[pos - count + i] = line->str[pos + i];
	line->str[pos - count + i] = '\0';
	ft_clear_line(line->len, line->left);
	line->len -= count;
	line->left = 0;
	write(1, line->str, line->len);
	return (0);
}
