/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <anorjen@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:42:39 by mgorczan          #+#    #+#             */
/*   Updated: 2019/11/30 17:51:50 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history_search.h"

t_history_session	*list_rewind_to_begin(t_history_session *dlst)
{
	if (dlst)
	{
		while (dlst->up)
			dlst = dlst->up;
	}
	return (dlst);
}

t_history_session	*list_rewind_to_end(t_history_session *dlst)
{
	if (dlst)
	{
		while (dlst->down)
			dlst = dlst->down;
	}
	return (dlst);
}

int					listlen(t_history_session *dlst)
{
	t_history_session	*tmp;
	int					i;

	i = 0;
	tmp = dlst;
	tmp = list_rewind_to_begin(tmp);
	while (tmp)
	{
		++i;
		tmp = tmp->down;
	}
	return (i);
}

int					arrlen(char **query)
{
	int i;

	i = 0;
	while (query[i] != NULL)
		++i;
	return (i);
}
