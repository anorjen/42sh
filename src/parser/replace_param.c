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

char	*replace_param_value(char *line, int *length, char *env)
{
	char	symbol;
	char	*word;
	char	*end;

	(*length)++;
	if (line[*length] == '+' || line[*length] == '-'
		|| line[*length] == '=' || line[*length] == '?')
		symbol = line[*length];
	else
		return (" ");
	(*length)++;
	end = ft_strchr(line + *length, '}');
	word = ft_strnew(end - line - *length);
	ft_strncpy(word, line + *length, end - line - *length);
	*length = end - line + 1;
	if (env && ft_strcmp(env, "") && symbol != '+')
		return (env);
	else if ((env && ft_strcmp(env, "") && symbol == '+')
				|| (env && !ft_strcmp(env, ""))
				||	(!env))
		return (word);
	return (NULL);
}

char	*replace_param(char *line, int i, int *length)
{
	int		flag;
	char	*env;

	flag = 0;
	if (line[i] == '#')
	{
		*length = ++i;
		flag = 1;
	}
	env = check_env_verb(line, i, length);
	if (line[*length] == ':')
		return (replace_param_value(line, length, env));
	else if (line[*length] == '%');
		//remove_suffix();
	else if (line[*length] == '#');
		//remove_prefix();
	else if (line[*length] == '}')
	{
		(*length)++;
		return (env);
	}
	parser_error_set(ft_strdup("42sh: bad substitution"));
	return (" ");
}
