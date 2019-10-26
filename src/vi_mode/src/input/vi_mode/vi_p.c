/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 19:10:02 by anorjen           #+#    #+#             */
/*   Updated: 2019/09/28 15:38:57 by anorjen          ###   ########.fr       */
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
