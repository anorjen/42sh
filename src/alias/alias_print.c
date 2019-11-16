/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 13:11:55 by rwalder-          #+#    #+#             */
/*   Updated: 2019/10/27 13:14:50 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias.h"

void	alias_print(void)
{
	int i;

	i = 0;
	while (i < (int)g_alias_value->size)
	{
		ft_printf("%s=%s\n", vector_get(g_alias_key, i),
			vector_get(g_alias_value, i));
		i++;
	}
}
