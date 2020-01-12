/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:52:41 by mgorczan          #+#    #+#             */
/*   Updated: 2020/01/12 18:21:46 by sbearded         ###   ########.fr       */
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
		write(2, g_error_parse_msg, ft_strlen(g_error_parse_msg));
		write(2, "\n", 1);
		free(g_error_parse_msg);
		g_error_parse_msg = NULL;
		free_arg(arg);
		return (1);
	}
	else
		return (0);
}
