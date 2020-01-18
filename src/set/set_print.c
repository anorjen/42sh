/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 13:22:23 by jcartwri          #+#    #+#             */
/*   Updated: 2020/01/18 19:21:22 by sbearded         ###   ########.fr       */
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
		write(proc->out_fdpipe, str, ft_strlen(str));
		write(proc->out_fdpipe, "=", 1);
		str = vector_get(g_set_value, i);
		write(proc->out_fdpipe, str, ft_strlen(str));
		write(proc->out_fdpipe, "\n", 1);
		i++;
	}
}
