/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstchange.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 13:49:17 by sbearded          #+#    #+#             */
/*   Updated: 2018/12/06 13:56:37 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstchange(t_list **head, void *data)
{
	t_list	*ptr;

	if (*head == NULL)
		return ;
	ptr = *head;
	while (ptr->next != NULL)
	{
		ptr->content = data;
		ptr = ptr->next;
	}
}
