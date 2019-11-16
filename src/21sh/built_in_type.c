/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 22:00:44 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 22:00:45 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_type(char *arg, char *path, int type)
{
	ft_printf("%s is ", arg);
	if (type == HASH_BUILT)
		ft_printf("a 42sh builtin\n");
	else if (type == 50)
		ft_printf("an alias for %s\n", path);
	else
		ft_printf("%s\n", path);
}

void	search_type(char *str)
{
	char	*res;
	int		i;

	i = 1;
	if (ft_strcmp((res = alias_get(str)), ""))
		return (print_type(str, res, 50));
	while (i < HASH_NUM)
	{
		phash_update();
		res = phash_search(str, i);
		if (res)
			return (print_type(str, res, i));
		i++;
	}
	if (access(str, F_OK) == 0)
		return (print_type(str, str, 100));
	ft_printf("%s not found\n", str);
}

int		type_shell(t_process *proc)
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
