/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:40:53 by sbearded          #+#    #+#             */
/*   Updated: 2019/12/03 17:15:52 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*param_exp_hash(t_exp *exp)
{
	size_t	len_env;
	char	*str;
	char	*word_rev;
	char	*tmp;
	char	*res;

	res = ft_strdup(exp->env);
	str = ft_strrev(exp->env);
	word_rev = ft_strrev(exp->word);
	len_env = ft_strlen(str);
	while (len_env > 0)
	{
		if (match(str + len_env - 1, word_rev))
		{
			tmp = ft_strsub(str, 0, len_env - 1);
			free(res);
			res = ft_strrev(tmp);
			free(tmp);
			break ;
		}
		len_env--;
	}
	free(str);
	free(word_rev);
	return (res);
}
