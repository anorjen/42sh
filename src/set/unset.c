/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 13:22:40 by rwalder-          #+#    #+#             */
/*   Updated: 2019/10/27 13:22:41 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set.h"

void	unset(char *key)
{
	int i;

	i = 0;
	while (g_set_key->arr[i] != NULL)
	{
		if (ft_strcmp(key, g_set_key->arr[i]) == 0)
		{
			free(vector_get(g_set_key, i));
			g_set_key->arr[i] = NULL;
			vector_del(g_set_key, i);
			free(vector_get(g_set_value, i));
			g_set_value->arr[i] = NULL;
			vector_del(g_set_value, i);
			set_update();
			return ;
		}
		i++;
	}
	set_update();
}
