/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_param.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:53:43 by sbearded          #+#    #+#             */
/*   Updated: 2020/01/18 12:26:05 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (ft_isalpha(line[(*length)]) || ft_isdigit(line[(*length)])
			|| line[(*length)] == '_')
		++(*length);
	exp.param = ft_strsub(line, i + exp.flag_exp + exp.flag_hash,
				(*length) - i - exp.flag_exp - exp.flag_hash);
	exp.env = ft_strdup(get_env(exp.param));
	return (parse_action(line, length, &exp));
}
