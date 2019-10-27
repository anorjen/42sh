/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 11:47:09 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 11:53:55 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_args(char ***args)
{
	char	**temp;
	char	*temp_str;
	int		total_len;
	int		i;

	temp = *args;
	total_len = 0;
	i = -1;
	while (temp[++i])
		total_len += ft_strlen(temp[i]) + 1;
	temp_str = ft_strnew(total_len);
	i = -1;
	while (temp[++i])
	{
		ft_strcpy(temp_str + ft_strlen(temp_str), temp[i]);
		ft_strcpy(temp_str + ft_strlen(temp_str), " ");
	}
	i = -1;
	while (temp[++i])
		ft_strdel(&temp[i]);
	ft_memdel((void**)args);
	*args = write_arg(temp_str);
	ft_strdel(&temp_str);
}

static char	**replace_on_alias(char **args, int i)
{
	char	*str;

	str = alias_get(args[i]);
	if (ft_strcmp(str, "") != 0 && ft_strcmp(args[0], "alias") != 0)
	{
		ft_strdel(&args[i]);
		args[i] = str;
		update_args(&args);
	}
	else
		ft_strdel(&str);
	return (args);
}

char		**replace_alias(char **argv)
{
	if (argv && argv[0])
		argv = replace_on_alias(argv, 0);
	return (argv);
}
