/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 13:53:12 by sbearded          #+#    #+#             */
/*   Updated: 2018/12/06 14:03:47 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list **head)
{
	t_list	*ptr;
	size_t	i;

	i = 1;
	if (*head == NULL)
		return ;
	ptr = *head;
	while (ptr->next != NULL)
	{
		ft_putstr(ptr->content);
		ptr = ptr->next;
	}
}
