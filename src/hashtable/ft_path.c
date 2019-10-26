/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:09:28 by sbearded          #+#    #+#             */
/*   Updated: 2019/09/28 16:56:54 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/hashtable.h"

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
