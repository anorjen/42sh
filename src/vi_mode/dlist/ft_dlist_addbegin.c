/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_addbegin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 19:03:07 by anorjen           #+#    #+#             */
/*   Updated: 2019/10/27 12:17:19 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"

void	ft_dlist_addbegin(t_dlist **alst, t_dlist *new)
{
	if (alst && new)
	{
		if (*alst)
		{
			while ((*alst)->prev != NULL)
				*alst = (*alst)->prev;
			new->prev = NULL;
			new->next = *alst;
			(*alst)->prev = new;
		}
		*alst = new;
	}
}
