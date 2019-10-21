/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_union.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 16:35:22 by anorjen           #+#    #+#             */
/*   Updated: 2019/06/03 19:15:01 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

static char	*addstr(char **dest, char *src, int pos)
{
	char	*buf;
	int		len;

	len = ft_strlen(*dest);
	buf = str_substr(*dest, pos, len - pos);
	ft_memcpy(&(*dest)[pos], src, ft_strlen(src));
	ft_memcpy(&(*dest)[pos + ft_strlen(src)], buf, len - pos);
	if (buf)
		free(buf);
	return (*dest);
}

static char	*newstr(char **dest, char *src, int pos, int size)
{
	char	*unstr;
	int		alloc;
	int		len_dest;
	int		len_src;

	len_dest = ft_strlen(*dest);
	len_src = ft_strlen(src);
	alloc = (size / BUFF + 1) * BUFF;
	unstr = ft_strnew(alloc);
	if (unstr)
	{
		ft_memcpy(unstr, *dest, pos);
		ft_memcpy(&(unstr[pos]), src, len_src);
		ft_memcpy(&(unstr[pos + len_src]), &(*dest)[pos], len_dest - pos);
		free(*dest);
	}
	return (unstr);
}

char		*str_union(char **dest, char *src, int pos)
{
	char	*unstr;
	int		size;
	int		alloc;
	int		len_dest;

	if (pos < 0 || *dest == NULL || dest == NULL || src == NULL)
		return (NULL);
	len_dest = ft_strlen(*dest);
	size = len_dest + ft_strlen(src);
	alloc = (len_dest / BUFF + (len_dest % BUFF > 0 ? 1 : 0)) * BUFF;
	if (alloc > size)
		unstr = addstr(dest, src, pos);
	else
		unstr = newstr(dest, src, pos, size);
	unstr[size] = '\0';
	return (unstr);
}
