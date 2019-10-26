/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 11:32:03 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/26 15:01:55 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*param_exp_equal(t_exp *exp)
{
	char	*res;

	if (!exp->env || ft_strequ(exp->env, ""))
	{
		set_env(exp->param, exp->word);
		res = ft_strdup(exp->word);
	}
	else
		res = ft_strdup(exp->env);
	return (res);
}
