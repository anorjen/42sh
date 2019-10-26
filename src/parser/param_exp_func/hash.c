/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 11:36:34 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/26 16:48:55 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*param_exp_hash(t_exp *exp)
{
	size_t	len_env;
	size_t	len_word;
	char	*res;

	len_env = ft_strlen(exp->env);
	len_word = ft_strlen(exp->word);
	if (!ft_strncmp(exp->env, exp->word, len_word))
		res = ft_strsub(exp->env, 0, (len_env - len_word));
	else
		res = ft_strdup(exp->env);
	return (res);
}
