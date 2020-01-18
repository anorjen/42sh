/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_addback.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:49:56 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 21:49:58 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

static	char	*create(char *str, char *src, int size)
{
	int	alloc;

	alloc = (size / BUFF + 1) * BUFF;
	str = ft_strnew(alloc);
	ft_memcpy(str, src, size);
	return (str);
}

char			*str_addback(char **dest, char *src, int size)
{
	char	*str;
	int		len_dest;
	int		alloc_dest;

	if (dest && *dest && (size <= 0 || !src))
		return (*dest);
	if (!(*dest) && src && size > 0)
		return (create(*dest, src, size));
	len_dest = ft_strlen(*dest);
	alloc_dest = (len_dest / BUFF + ((len_dest % BUFF) > 0 ? 1 : 0)) * BUFF;
	if (alloc_dest - len_dest < size)
	{
		alloc_dest = ((len_dest + size) / BUFF + 1) * BUFF;
		if ((str = ft_strnew(alloc_dest)) == NULL)
			return (NULL);
		ft_memcpy(str, *dest, len_dest);
		free(*dest);
		*dest = str;
	}
	ft_memcpy(*dest + len_dest, src, size);
	(*dest)[len_dest + size] = '\0';
	return (*dest);
}
