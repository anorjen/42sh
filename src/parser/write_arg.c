/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 18:19:50 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/20 18:19:51 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		spec_token(char *line, int j)
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
	else if (line[j] == '<' && line[j + 1] == '&')
		return (TOKEN_AGRAGATION);
	else if (line[j] == '<')
		return (TOKEN_INPUTPATH);
	else if (line[j] == '>' && line[j + 1] == '>')
		return (TOKEN_UPPEND);
	else if (line[j] == '>' && line[j + 1] == '&')
		return (TOKEN_AGRAGATION);
	else if (line[j] == '>')
		return (TOKEN_OUTPUTPATH);
	else
		return (0);
}

int		lenght_token(char *line, int j)
{
	int		lenght;
	char	temp;

	lenght = 0;
	if ((lenght = spec_token(line, j)))
		return (lenght);
	while (line[j] && !is_delimetr(line[j]) && !spec_token(line, j))
	{
		if (line[j] == '\"' || line[j] == '\'')
		{
			temp = line[j++];
			lenght++;
			while (line[j] && line[j] != temp)
			{
				++j;
				lenght++;
			}
			lenght += line[j] ? 1 : 0;
			j += line[j] ? 1 : 0;
		}
		else
		{
			lenght++;
			++j;
		}
	}
	return (lenght);
}

char    *get_token(char *line, int j, int lenght)
{
	char	*token;
	int i;

	i = 0;
	token = (char*)malloc(sizeof(char) * lenght + 1);
	if (!token)
		exit(1);
	while (i < lenght)
		token[i++] = line[j++];
	return (token);
}

int			is_delimetr(char ch)
{
	if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || ch == '\v')
		return (1);
	return (0);
}

int	count_argv(char *line)
{
	int		i;
	char	temp;
	int count;

	i = 0;
	count = 0;
	while (line && line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			temp = (line[i++] == '\"') ? '\"' : '\'';
			while (line[i] && line[i] != temp)
				++i;
			i += line[i] ? 1 : 0;
			++count;
		}
		else if ((temp = spec_token(line, i)))
		{
			i += temp;
			++count;
		}
		else if (!(is_delimetr(line[i])))
		{
			while (line[i] && !(is_delimetr(line[i])) && !spec_token(line, i))
				++i;
			++count;			
		}
		else
			++i;
	}
	return (count);
}

char    **write_arg(char *line)
{
	char    **arg;
	int     i;
	int     j;
	int		lenght;
	int		count_arg;

	i = 0;
	j = 0;
	lenght = 0;
	count_arg = count_argv(line);
	if (!count_arg)
		return (NULL);
	if ((arg = (char**)malloc(sizeof(char*) * (count_arg + 1))) == NULL)
		exit(1);
	while (i < count_arg)
	{
		while (line[j] && is_delimetr(line[j]))
			++j;
		lenght = lenght_token(line, j);
		arg[i] = get_token(line, j, lenght);       
		j += lenght;
		++i;
	}
	arg[i] = NULL;
	
	return (arg);
}

