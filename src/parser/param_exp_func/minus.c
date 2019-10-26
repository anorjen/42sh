/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 11:29:04 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/26 15:02:31 by sbearded         ###   ########.fr       */
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
