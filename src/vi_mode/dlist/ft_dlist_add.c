/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:07:41 by anorjen           #+#    #+#             */
/*   Updated: 2019/06/05 19:57:23 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"

void	ft_dlist_add(t_dlist **dlst, t_dlist *new)
{
	t_dlist	*pv;
	t_dlist	*nx;

	pv = NULL;
	nx = NULL;
	if(dlst && new)
	{
		if (*dlst)
		{
			pv = (*dlst)->prev;
			new->prev = pv;
			new->next = *dlst;
			(*dlst)->prev = new;
			if (pv)
				pv->next = new;
		}
		*dlst = new;
	}
}