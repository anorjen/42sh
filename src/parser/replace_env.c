/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:55:23 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/20 17:55:25 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	replace_str(char **chang_line, int i, int lenght, char *env_verb)
{
	char *temp;
	char *tmp;

	temp = *chang_line;
	*chang_line = ft_strsub(temp, 0, i);
	tmp = *chang_line;
	*chang_line = ft_strjoin(tmp, env_verb);
	free(tmp);
	tmp = *chang_line;
	*chang_line = ft_strjoin(tmp, &temp[lenght]);
	free(tmp);
	free(temp);
	
}

char	*check_env_verb(char *line, int i, int *lenght, char **environ)
{
	char	*temp;
	char	*temp2;

	*lenght = ++i;
	if (!ft_isalpha(line[i]) && !ft_isdigit(line[i]))
	{
		return ("$");
	}
	while (ft_isalpha(line[(*lenght)]) || ft_isdigit(line[(*lenght)]))
		++(*lenght);
	temp = ft_strsub(line, i, (*lenght) - i);
	i = (*lenght);
	if (getenv(temp))
	{
		temp2 = getenv(temp);
		free(temp);
		return (temp2);
	}
	free(temp);
	return (" ");
}

static int		miss_quote(char **chang_line, int i, char **env)
{
	int	lenght;
	char *env_verb;

	lenght = 0;
	if ((*chang_line)[i] == '\'')
	{
        ++i;
		while ((*chang_line)[i] && (*chang_line)[i] != '\'')
			++i;
		i += (*chang_line)[i] ? 1 : 0;
	}
	else if ((*chang_line)[i] == '\"')
	{
        ++i;
		while ((*chang_line)[i] && (*chang_line)[i] != '\"')
		{
			if ((*chang_line)[i] == '$')
			{
				lenght = i;
				env_verb = check_env_verb(*chang_line, i, &lenght, env);
				if (!ft_strcmp(env_verb, " "))
					cut_str(chang_line, i, lenght);
				else if (ft_strcmp(env_verb, "$"))
				{
					replace_str(chang_line, i, lenght, env_verb);
					i += ft_strlen(env_verb);
				}
				else
					++i;
			}
			else
				++i;
		}
		i += (*chang_line)[i] ? 1 : 0;
	}
	return (i);
}

char    *replace_env(char *line, char **env)
{
	int	i;
	int	lenght;
	char *chang_line;
	char *env_verb;


	i = 0;
	chang_line = line;
	while (chang_line && chang_line[i])
	{
		if (chang_line[i] == '\'' || chang_line[i] == '\"')
			i = miss_quote(&chang_line, i, env);
		else if (chang_line[i] == '$')
		{
			lenght = i;
			env_verb = check_env_verb(chang_line, i, &lenght, env);
			if (!ft_strcmp(env_verb, " "))
				cut_str(&chang_line, i, lenght);
			else if (ft_strcmp(env_verb, "$"))
			{
			    replace_str(&chang_line, i, lenght, env_verb);
				i += ft_strlen(env_verb);
			}
			else
			    ++i;
		}
		else
			++i;
	}
	return (chang_line);
}
