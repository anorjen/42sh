/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:41:36 by sbearded          #+#    #+#             */
/*   Updated: 2019/11/19 16:41:53 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cd_check_flags(char *flags)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
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
	return (res);
}
