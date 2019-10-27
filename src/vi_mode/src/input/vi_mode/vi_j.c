/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_j.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:27:31 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:27:32 by mgorczan         ###   ########.fr       */
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
