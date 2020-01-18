/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:40:57 by sbearded          #+#    #+#             */
/*   Updated: 2019/12/03 17:49:19 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	while_loop(size_t len_env, char *str, char *word_rev, char **res)
{
	char	*tmp;
	size_t	i;

	i = 0;
	while (i < len_env)
	{
		if (match(str + i, word_rev))
		{
			tmp = ft_strsub(str, 0, i);
			free(*res);
			*res = ft_strrev(tmp);
			free(tmp);
			break ;
		}
		i++;
	}
}

char		*param_exp_hash_d(t_exp *exp)
{
	size_t	len_env;
	char	*str;
	char	*word_rev;
	char	*res;

	res = ft_strdup(exp->env);
	str = ft_strrev(exp->env);
	word_rev = ft_strrev(exp->word);
	len_env = ft_strlen(str);
	while_loop(len_env, str, word_rev, &res);
	free(str);
	free(word_rev);
	return (res);
}
