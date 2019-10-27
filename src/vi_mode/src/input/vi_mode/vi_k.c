/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_k.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:27:38 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:27:39 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

int		vi_k(t_line *line, int count)
{
	t_dlist	*tmp;
	t_dlist	*elem;
	int		size;

	if (is_str(line->str))
	{
		tmp = g_history;
		elem = ft_dlist_new(line->str, line->len);
		size = ft_dlist_size(tmp);
		count = size - count;
		if (count <= 0)
			ft_dlist_addback(&tmp, elem);
		else
		{
			tmp = ft_dlist_rewind(tmp);
			while (tmp->next && count--)
				tmp = tmp->next;
			ft_dlist_add(&tmp, elem);
		}
	}
	return (0);
}
