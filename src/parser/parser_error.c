/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:52:41 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:52:43 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*g_error_parse_msg = NULL;

void	parser_error_set(char *msg)
{
	g_error_parse_msg = msg;
}

int		parser_error_print(char **arg)
{
	if (g_error_parse_msg)
	{
		ft_printf("%s\n", g_error_parse_msg);
		free(g_error_parse_msg);
		g_error_parse_msg = NULL;
		free_arg(arg);
		return (1);
	}
	else
		return (0);
}
