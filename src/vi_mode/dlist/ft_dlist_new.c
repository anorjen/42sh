/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:50:58 by anorjen           #+#    #+#             */
/*   Updated: 2019/06/05 18:27:11 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"

t_dlist	*ft_dlist_new(void const *content, size_t content_size)
{
	t_dlist	*res;

	res = ft_memalloc(sizeof(t_dlist));
	if (res)
	{
		if (content)
		{
			res->content = ft_memalloc(content_size);
			if (res->content)
			{
				ft_memcpy(res->content, content, content_size);
				res->content_size = content_size;
			}
			else
				res->content_size = 0;
		}
		else
		{
			res->content = NULL;
			res->content_size = 0;
		}
		res->next = NULL;
		res->prev = NULL;
	}
	return (res);
}
