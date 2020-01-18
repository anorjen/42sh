/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 14:13:52 by sbearded          #+#    #+#             */
/*   Updated: 2018/12/05 16:52:18 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*new_arr;
	unsigned char	*old_arr;

	i = -1;
	new_arr = (unsigned char *)dst;
	old_arr = (unsigned char *)src;
	if (new_arr > old_arr)
		while (len-- > 0)
			new_arr[len] = old_arr[len];
	else
		while (++i < len)
			new_arr[i] = old_arr[i];
	return (new_arr);
}
