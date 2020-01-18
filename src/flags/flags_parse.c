/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 18:09:24 by sbearded          #+#    #+#             */
/*   Updated: 2020/01/18 18:09:28 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*flags_parse(char **argv, int *i)
{
	char	*flags;
	char	*tmp;

	flags = NULL;
	*i = 1;
	while (argv[*i] && argv[*i][0] == '-' && argv[*i][1])
	{
		tmp = flags;
		flags = ft_strjoin(flags, argv[*i] + 1);
		free(tmp);
		(*i)++;
	}
	return (flags);
}
