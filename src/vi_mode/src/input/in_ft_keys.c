/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_ft_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:14:47 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 21:14:49 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

void	ft_keys(int key, char **line, int *len, int *left)
{
	if (is_arrow(key))
		arrows(key, line, len, left);
	else if (key == KC_HOME)
		ft_key_home(len, left);
	else if (key == KC_END)
		ft_key_end(*len, left);
	else if (key == KC_DEL)
		ft_delkey(line, len, left);
	else if (key == KC_NEXT_WORD)
		ft_key_next(*line, *len, left);
	else if (key == KC_PREV_WORD)
		ft_key_prev(*line, *len, left);
}

void	ft_key_home(int *len, int *left)
{
	int		pos;

	pos = *len - *left + 1;
	while (--pos > 0)
		tputs(g_term->le, 1, ft_put);
	*left = *len;
}

void	ft_key_end(int len, int *left)
{
	int		pos;

	pos = len - *left;
	while (pos++ < len)
		tputs(g_term->nd, 1, ft_put);
	*left = 0;
}

void	ft_key_prev(char *line, int len, int *left)
{
	int	pos;

	pos = len - *left;
	while (pos > 0)
	{
		tputs(g_term->le, 1, ft_put);
		pos--;
		if (line[pos - 1] == ' ' && line[pos] != ' ')
			break ;
	}
	(*left) = len - pos;
}

void	ft_key_next(char *line, int len, int *left)
{
	int	pos;

	pos = len - *left;
	while (pos < len)
	{
		pos++;
		tputs(g_term->nd, 1, ft_put);
		if (line[pos - 1] == ' ' && line[pos] != ' ')
			break ;
	}
	*left = len - pos;
}
