/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plus.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 11:30:59 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/26 15:02:42 by sbearded         ###   ########.fr       */
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
