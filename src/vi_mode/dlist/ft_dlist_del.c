/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_del.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 19:16:35 by anorjen           #+#    #+#             */
/*   Updated: 2019/06/05 20:55:08 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"

void	ft_dlist_del(t_dlist **dlst)
{
	t_dlist	*tmp;

	*dlst = ft_dlist_rewind(*dlst);
	while (*dlst)
	{
		tmp = (*dlst)->next;
		free((*dlst)->content);
		free(*dlst);
		*dlst = tmp;
	}
	*dlst = NULL;
}
