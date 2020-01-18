/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_delone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:51:38 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 21:51:39 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"

void	ft_dlist_delone(t_dlist **lst)
{
	t_dlist	*pv;
	t_dlist	*nx;

	pv = NULL;
	nx = NULL;
	if (lst && *lst)
	{
		nx = (*lst)->next;
		pv = (*lst)->prev;
		if ((*lst)->content)
			free((*lst)->content);
		free(*lst);
		*lst = nx;
		if (nx)
			nx->prev = pv;
		if (pv)
			pv->next = nx;
	}
}
