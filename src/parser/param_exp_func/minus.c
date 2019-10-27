/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:41:01 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:41:02 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*param_exp_minus(t_exp *exp)
{
	char	*res;

	if (!exp->env || ft_strequ(exp->env, ""))
		res = ft_strdup(exp->word);
	else
		res = ft_strdup(exp->env);
	return (res);
}
