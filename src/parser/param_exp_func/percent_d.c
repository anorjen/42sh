/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:41:09 by mgorczan          #+#    #+#             */
/*   Updated: 2019/12/06 14:55:38 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*param_exp_percent_d(t_exp *exp)
{
	size_t	len_env;
	size_t	i;

	len_env = ft_strlen(exp->env);
	i = 0;
	while (i < len_env)
	{
		if (match(exp->env + i, exp->word))
			return (ft_strsub(exp->env, 0, i));
		i++;
	}
	return (ft_strdup(exp->env));
}
