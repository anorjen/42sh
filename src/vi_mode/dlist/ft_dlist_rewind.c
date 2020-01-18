/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_rewind.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:51:47 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 21:51:48 by sbearded         ###   ########.fr       */
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
