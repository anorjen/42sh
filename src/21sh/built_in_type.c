/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:37:51 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/12 15:33:26 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	print_type(char *arg, char *path, int type)
{
	ft_printf("%s is ", arg);
	if (type == HASH_BUILT)
		ft_printf("a 42sh builtin\n");
	else
		ft_printf("%s\n", path);
}

char	*search_type(char *str)
{
	char	*res;
	int		i;

	i = 1;
	while (i < HASH_NUM)
	{
		res = phash_search(str, i);
		if (res)
			print_type(str, res, i);
		i++;
	}
	return (res);
}

int	type_shell(t_process *proc)
{
	char	**query;

	query = proc->query + 1;
	while (query && *query)
	{
		search_type(*query);
		query++;
	}
	return (0);
}
