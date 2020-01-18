/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eh_ft_list_del.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:12:55 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 21:12:59 by sbearded         ###   ########.fr       */
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
