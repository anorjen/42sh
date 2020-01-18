/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_del.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:51:33 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 21:51:34 by sbearded         ###   ########.fr       */
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
