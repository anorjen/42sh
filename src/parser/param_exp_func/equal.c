/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:40:46 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:40:47 by mgorczan         ###   ########.fr       */
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
