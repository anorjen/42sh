/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 13:21:32 by rwalder-          #+#    #+#             */
/*   Updated: 2019/11/23 18:08:05 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set.h"

int	ms_unset(t_process *proc)
{
	int		i;
	char	**args;

	i = 0;
	while (proc->query[++i])
	{
		unset(proc->query[i]);
		args = ft_memalloc(sizeof(char *) * 3);
		args[0] = ft_strdup("unsetenv");
		args[1] = ft_strdup(proc->query[i]);
		args[2] = NULL;
		kazekage(args);
	}
	return (1);
}
