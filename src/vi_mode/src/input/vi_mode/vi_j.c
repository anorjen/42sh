/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_j.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:52:41 by anorjen           #+#    #+#             */
/*   Updated: 2019/09/28 15:38:59 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

int		vi_j(t_line *line, int count)
{
	t_dlist	*tmp;
	t_dlist	*elem;

	if (is_str(line->str))
	{
		tmp = g_history;
		elem = ft_dlist_new(line->str, line->len);
		tmp = ft_dlist_rewind(tmp);
		while (tmp->next && count--)
			tmp = tmp->next;
		ft_dlist_add(&tmp, elem);
	}
	return (0);
}
