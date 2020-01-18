/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 18:22:21 by yharwyn-          #+#    #+#             */
/*   Updated: 2020/01/18 18:22:25 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int				check_access(char **files, int id)
{
	int			i;

	id = 0;
	i = 0;
	while (files[i])
	{
		if (access(files[i], F_OK) == -1)
		{
			ft_printf("21sh: %s: No such file or directory\n", files[i]);
			return (0);
		}
		++i;
	}
	return (1);
}
