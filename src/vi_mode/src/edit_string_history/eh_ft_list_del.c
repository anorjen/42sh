/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eh_ft_list_del.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:38:42 by anorjen           #+#    #+#             */
/*   Updated: 2019/09/28 15:40:20 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

void	ft_list_del(t_list **lst)
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
}
