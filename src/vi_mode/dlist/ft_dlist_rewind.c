/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_rewind.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 15:40:00 by anorjen           #+#    #+#             */
/*   Updated: 2019/06/05 18:27:19 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"

t_dlist	*ft_dlist_rewind(t_dlist *dlst)
{
	if (dlst)
	{
		while (dlst->prev)
			dlst = dlst->prev;
	}
	return (dlst);
}
