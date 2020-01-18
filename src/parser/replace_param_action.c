/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_param_action.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:58:05 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/12/06 15:03:59 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_exp(t_exp *exp)
{
	free(exp->param);
	free(exp->word);
	free(exp->action);
	if (exp->env)
		free(exp->env);
}

char		*do_hash(char *str)
{
	char	*tmp;

	tmp = str;
	str = ft_itoa(ft_strlen(str));
	free(tmp);
	return (str);
}

char		*do_replace(t_exp *exp)
{
	char	*error;
	char	*res;

	if (exp->action)
	{
		if (exp->func)
			res = exp->func(exp);
		else
		{
			error = ft_strjoin("42sh: parameter expansion: illegal option ",
								exp->action);
			parser_error_set(error);
			free_exp(exp);
			return (ft_strdup(" "));
		}
	}
	else
		res = exp->env ? ft_strdup(exp->env) : ft_strdup(" ");
	if (exp->flag_hash)
		res = do_hash(res);
	free_exp(exp);
	return (res);
}

void		choose_action(char *line, int *length, t_exp *exp)
{
	char	*(*func)(t_exp *);
	char	*str;

	str = ft_strsub(line, *length, 2);
	func = phash_search(str, HASH_PARAM_EXP);
	if (func)
		*length += 2;
	else
	{
		free(str);
		str = ft_strsub(line, *length, 1);
		func = phash_search(str, HASH_PARAM_EXP);
		*length += 1;
	}
	exp->action = str;
	exp->func = func;
}

char		*parse_action(char *line, int *length, t_exp *exp)
{
	int	counter;
	int	i;

	counter = 0;
	if (exp->flag_exp == 0)
	{
		free(exp->param);
		if (exp->env)
			return (exp->env);
		return (ft_strdup(" "));
	}
	exp->action = NULL;
	if (line[*length] != '}')
		choose_action(line, length, exp);
	i = *length;
	while (line[*length] && line[*length] != '}')
		++(*length);
	exp->word = ft_strsub(line, i, (*length) - i);
	++(*length);
	return (do_replace(exp));
}
