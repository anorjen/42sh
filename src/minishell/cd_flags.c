/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:41:36 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/11/28 20:22:49 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cd_check_flags(char *flags)
{
	int	i;
	int	res;

	i = 0;
	res = CD_L_FLAG;
	while (flags[i])
	{
		if (flags[i] == 'L')
			res = CD_L_FLAG;
		else if (flags[i] == 'P')
			res = CD_P_FLAG;
		else
		{
			print_error("42sh: cd: invalid option", "");
			print_error("cd: ", "usage: cd [-L|-P] [dir]");
			return (0);
		}
		i++;
	}
	free(flags);
	return (res);
}
