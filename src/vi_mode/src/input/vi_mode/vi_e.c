/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_e.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:26:37 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 21:26:38 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

static void	ft_key_next_end(char *line, int len, int *left)
{
	int	pos;

	pos = len - *left;
	while (pos < len)
	{
		pos++;
		tputs(g_term->nd, 1, ft_put);
		if (line[pos + 1] == ' ' && line[pos] != ' ')
			break ;
	}
	*left = len - pos;
}

int			vi_e(t_line *line, int count)
{
	while (count-- && line->left > 0)
		ft_key_next_end(line->str, line->len, &(line->left));
	return (0);
}
