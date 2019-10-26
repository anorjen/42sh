/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:16:07 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/10/26 17:15:14 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char		*ft_strjoiner(char const *s1, char const *s2)
{
	char	*new_arr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	new_arr = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (new_arr == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		new_arr[i] = s1[i];
		++i;
	}
	new_arr[i++] = '/';
	while (s2[j] != '\0')
	{
		new_arr[i] = s2[j];
		++j;
		++i;
	}
	return (new_arr);
}

static void	shift_to_left(char *str)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str) - 1;
	while (i < len)
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i] = '\0';
}

static char	*string_to_env(char *str)
{
	char	*line;
	t_vault	*env_value;

	shift_to_left(str);
	if (g_env != NULL && (env_value = search_key(g_env->vault, str)) != NULL)
	{
		line = ft_memalloc(100);
		ft_strcpy(line, env_value->path);
		ft_memdel((void **)&str);
		return (line);
	}
	line = ft_strdup(" ");
	return (line);
}

void		string_var_parser(char **line)
{
	int i;
	int j;

	i = 0;
	while (line[i] != 0)
	{
		j = 0;
		while (line[i][j] != '\0' && line[i][0] != '\'')
		{
			if (line[i][j] == '$')
			{
				line[i] = string_to_env(line[i]);
				break ;
			}
			j++;
		}
		i++;
	}
}

t_vault		*environ_grab(t_vault *root)
{
	char		**environ;
	int			i;

	i = 0;
	environ = g_sh->env;
	while (environ[i] != NULL)
	{
		root = append_env(root, environ[i]);
		i++;
	}
	return (root);
}
