/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_deinit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 13:11:03 by rwalder-          #+#    #+#             */
/*   Updated: 2019/10/27 13:11:12 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias.h"

void	delete_copy_alias(void)
{
	int	i;

	i = 0;
	if (g_alias == NULL || g_alias[0] == NULL)
		return ;
	while (g_alias[i] != NULL)
	{
		ft_strdel(&g_alias[i]);
		i++;
	}
	ft_memdel((void **)&g_alias);
}

void	alias_deinit(void)
{
	char	*str;

	delete_copy_alias();
	while ((str = vector_get(g_alias_key, 0)) != NULL)
	{
		ft_strdel(&str);
		vector_del(g_alias_key, 0);
	}
	while ((str = vector_get(g_alias_value, 0)) != NULL)
	{
		ft_strdel(&str);
		vector_del(g_alias_value, 0);
	}
	vector_deinit(&g_alias_key);
	vector_deinit(&g_alias_value);
}
