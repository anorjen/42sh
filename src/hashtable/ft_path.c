/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:44:05 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:44:06 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

char	*ft_get_path(char *path, char *name)
{
	char	*new_path;
	char	*tmp;

	new_path = ft_strnew(ft_strlen(path) + ft_strlen(name) + 1);
	tmp = new_path;
	while (path && *path)
		*(tmp++) = *(path++);
	if (!*path || *(path - 1) != '/')
		*(tmp++) = '/';
	while (name && *name)
		*(tmp++) = *(name++);
	*tmp = '\0';
	return (new_path);
}
