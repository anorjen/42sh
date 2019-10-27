/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:27:51 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:27:53 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

int		vi_p(t_line *line, int count)
{
	arrow_right(&(line->left));
	while (count--)
		ft_paste(&(line->str), &(line->len), &(line->left), g_strbuf);
	return (0);
}

int		vi_pb(t_line *line, int count)
{
	while (count--)
		ft_paste(&(line->str), &(line->len), &(line->left), g_strbuf);
	return (0);
}
