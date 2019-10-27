/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plus.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:41:13 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:41:14 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*param_exp_plus(t_exp *exp)
{
	char	*res;

	if (!exp->env || ft_strequ(exp->env, ""))
		res = ft_strdup(" ");
	else
		res = ft_strdup(exp->word);
	return (res);
}
