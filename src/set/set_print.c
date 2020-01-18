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

void	set_print(t_process *proc)
{
	int		i;
	char	*str;

	i = 0;
	while (i < (int)g_set_value->size)
	{
		str = vector_get(g_set_key, i);
		write(proc->out_fdPIPE, str, ft_strlen(str));
		write(proc->out_fdPIPE, "=", 1);
		str = vector_get(g_set_value, i);
		write(proc->out_fdPIPE, str, ft_strlen(str));
		write(proc->out_fdPIPE, "\n", 1);
		i++;
	}
}
