/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:07:41 by anorjen           #+#    #+#             */
/*   Updated: 2019/10/27 12:17:46 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"

void	ft_dlist_add(t_dlist **dlst, t_dlist *new)
{
	t_dlist	*pv;
	t_dlist	*nx;

	pv = NULL;
	nx = NULL;
	if (dlst && new)
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
