/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_delone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:16:25 by anorjen           #+#    #+#             */
/*   Updated: 2019/06/05 18:26:56 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"

void	ft_dlist_delone(t_dlist **lst)
{
	t_dlist	*pv;
	t_dlist	*nx;

	pv = NULL;
	nx = NULL;
	if(lst && *lst)
	{
		nx = (*lst)->next;
		pv = (*lst)->prev;
		if((*lst)->content)
			free((*lst)->content);
		free(*lst);
		*lst = nx;
		if (nx)
			nx->prev = pv;
		if (pv)
			pv->next = nx;
	}
}
