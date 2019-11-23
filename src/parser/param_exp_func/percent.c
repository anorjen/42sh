/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:41:05 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:41:06 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*param_exp_percent(t_exp *exp)
{
	size_t	len_env;
	size_t	len_word;
	char	*res;

	len_env = ft_strlen(exp->env);
	len_word = ft_strlen(exp->word);
	if (ft_strequ(exp->env + (len_env - len_word), exp->word))
		res = ft_strsub(exp->env, 0, (len_env - len_word));
	else
		res = ft_strdup(exp->env);
	return (res);
}
