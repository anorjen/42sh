/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_param.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:01:12 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 14:42:56 by sbearded         ###   ########.fr       */
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
	char	*(*func)(t_exp *);
	char	*error;
	char	*res;

	if (ft_strcmp(exp->action, ""))
	{
		func = phash_search(exp->action, HASH_PARAM_EXP);
		if (func)
			res = func(exp);
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
		res = ft_strdup(exp->env);
	if (exp->flag_hash)
		res = do_hash(res);
	free_exp(exp);
	return (res);
}

char		*parse_action(char *line, int *length, t_exp *exp)
{
	int	counter;
	int	i;

	if (!exp->env)
		exp->env = ft_strdup(" ");
	counter = 0;
	if (exp->flag_exp == 0)
	{
		free(exp->param);
		if (exp->env)
			return (exp->env);
		return (ft_strdup(" "));
	}
	i = *length;
	while (line[*length] && !ft_isdigit(line[*length])
			&& !ft_isalpha(line[*length]) && line[*length] != '}')
		++(*length);
	exp->action = ft_strsub(line, i, (*length) - i);
	i = *length;
	while (line[*length] && line[*length] != '}')
		++(*length);
	exp->word = ft_strsub(line, i, (*length) - i);
	++(*length);
	return (do_replace(exp));
}

char		*replace_param(char *line, int i, int *length)
{
	t_exp	exp;

	*length = ++i;
	if (line[i] == '{')
	{
		exp.flag_exp = 1;
		++(*length);
	}
	else if (ft_isalpha(line[i]) || ft_isdigit(line[i]))
		exp.flag_exp = 0;
	else
		return (ft_strdup("$"));
	exp.flag_hash = 0;
	if (line[(*length)] == '#')
	{
		exp.flag_hash = 1;
		++(*length);
	}
	while (ft_isalpha(line[(*length)]) || ft_isdigit(line[(*length)]))
		++(*length);
	exp.param = ft_strsub(line, i + exp.flag_exp + exp.flag_hash,
				(*length) - i - exp.flag_exp - exp.flag_hash);
	exp.env = ft_strdup(get_env(exp.param));
	return (parse_action(line, length, &exp));
}
