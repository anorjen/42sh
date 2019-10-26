/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   question.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 11:32:40 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/26 15:02:52 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*param_exp_question(t_exp *exp)
{
	char	*res;
	char	*tmp;

	if (!exp->env || ft_strequ(exp->env, ""))
	{
		tmp = ft_strjoin("42sh: ", exp->param);
		res = ft_strjoin(tmp, ": ");
		free(tmp);
		tmp = ft_strjoin(res, exp->word);
		parser_error_set(tmp);
	}
	else
		res = ft_strdup(exp->env);
	return (res);
}
