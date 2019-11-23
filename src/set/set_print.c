/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 13:22:23 by rwalder-          #+#    #+#             */
/*   Updated: 2019/10/27 13:24:21 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set.h"

void	set_print(void)
{
	int i;

	i = 0;
	while (i < (int)g_set_value->size)
	{
		ft_printf("%s=%s\n", vector_get(g_set_key, i),
			vector_get(g_set_value, i));
		i++;
	}
}
