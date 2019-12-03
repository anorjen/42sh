/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:41:05 by mgorczan          #+#    #+#             */
/*   Updated: 2019/12/03 16:15:14 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*param_exp_percent(t_exp *exp)
{
	size_t	len_env;

	len_env = ft_strlen(exp->env);
	while (len_env > 0)
	{
		if (match(exp->env + len_env - 1, exp->word))
			return (ft_strsub(exp->env, 0, len_env - 1));
		len_env--;
	}
	return (ft_strdup(exp->env));
}
