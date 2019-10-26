/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_param.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:01:12 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/24 14:39:08 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*parse_action(char *line, int *length, t_exp *exp)
{
	if (exp->flag_exp == 0 || line[*length] == '}')
	{
		free(exp->param);
		if (exp->env)
			return (exp->env);
		return (" ");
	}
	else if (line[*length] == ':')
	{
		(*length)++;
		line[*length] == '+' ? exp->action = S_PLUS : NULL;
		line[*length] == '-' ? exp->action = S_MINUS : NULL;
		line[*length] == '?' ? exp->action = S_QUEST : NULL;
		line[*length] == '=' ? exp->action = S_EQUAL : NULL;
		
	}
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
		return ("$");
	exp.flag_hash = 0;
	if (line[(*length)] == '#')
	{
		exp.flag_hash = 1;
		++(*length);
	}
	while (ft_isalpha(line[(*length)]) || ft_isdigit(line[(*length)]))
		++(*length);
	exp.param = ft_strsub(line, i + exp.flag_exp, (*length) - i + exp.flag_exp);
	exp.env = get_env(exp.param);
	return (parse_action(line, length, &exp));
}
