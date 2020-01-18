/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assist_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 21:41:11 by sbearded          #+#    #+#             */
/*   Updated: 2019/07/27 15:09:36 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_agregation(char *line, int j)
{
	if (line[j] && (line[j] == '<' || line[j] <= '>') && line[j + 1] == '&')
		return (2);
	return (0);
}

int	spec_token2(char *line, int j)
{
	if (ft_isdigit(line[j]) && line[j + 1] == '<' && line[j + 2] != '&')
		return (2);
	else if (line[j] == '>' && line[j + 1] == '>')
		return (TOKEN_UPPEND);
	else if (line[j] == '>' && line[j + 1] != '&')
		return (TOKEN_OUTPUTPATH);
	else if (ft_isdigit(line[j]) && line[j + 1] == '>' && line[j + 2] != '&')
		return (2);
	else if (line[j] == '>' && line[j + 1] == '&')
		return (2);
	else if (line[j] == '<' && line[j + 1] == '&')
		return (2);
	else if (ft_isdigit(line[j]) && line[j + 1] == '>' && line[j + 2] == '&')
		return (3);
	else if (ft_isdigit(line[j]) && line[j + 1] == '<' && line[j + 2] == '&')
		return (3);
	else if (line[j] == ';')
		return (1);
	else
		return (0);
}

int	spec_token(char *line, int j)
{
	if (!line || !line[j])
		return (0);
	else if (line[j] == '&' && line[j + 1] == '&')
		return (TOKEN_AND);
	else if (line[j] == '&')
		return (TOKEN_BACKGRAUND);
	else if (line[j] == '|' && line[j + 1] == '|')
		return (TOKEN_OR);
	else if (line[j] == '|')
		return (TOKEN_PIPE);
	else if (line[j] == '<' && line[j + 1] == '<')
		return (TOKEN_HEREDOK);
	else if (line[j] == '<' && line[j + 1] != '&')
		return (TOKEN_INPUTPATH);
	else
		return (spec_token2(line, j));
}

int	is_delimetr(char ch)
{
	if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || ch == '\v')
		return (1);
	return (0);
}

int	is_specdel(char *line, int i)
{
	if (!line)
		return (0);
	if (line[i] == '|' && line[i + 1] == '|')
		return (2);
	else if (line[i] == '|')
		return (1);
	else if (line[i] == '&' && line[i + 1] == '&')
		return (2);
	else if (line[i] == '&')
		return (1);
	return (0);
}
