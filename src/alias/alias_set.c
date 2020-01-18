/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcartwri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 13:12:04 by jcartwri          #+#    #+#             */
/*   Updated: 2019/10/27 13:12:06 by jcartwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias.h"

void	alias_set(char *key, char *value)
{
	int		i;
	char	*str;

	i = 0;
	while ((str = vector_get(g_alias_key, i)) != NULL)
	{
		if (ft_strcmp(str, key) == 0)
		{
			free(vector_get(g_alias_value, i));
			vector_set(g_alias_value, i, ft_strdup(value));
			alias_update();
			return ;
		}
		i++;
	}
	vector_add(g_alias_key, ft_strdup(key));
	vector_add(g_alias_value, ft_strdup(value));
	alias_update();
}
