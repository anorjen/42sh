/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcartwri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 17:59:48 by jcartwri          #+#    #+#             */
/*   Updated: 2019/06/18 17:59:50 by jcartwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set.h"

static void env_set(char *key, char *value)
{
    char **args;

    args = ft_memalloc(sizeof(char *) * 3);
    args[0] = ft_strdup("setenv");
    args[2] = NULL;
    args[1] = ft_strnew(ft_strlen(key) + ft_strlen(value) + 1);
    ft_strcpy(args[1], key);
    ft_strcpy(args[1] + ft_strlen(args[1]), "=");
    ft_strcpy(args[1] + ft_strlen(args[1]), value);
    kazekage(args);
}

int ms_export(t_process *proc)
{
	char *str;
	char **arr;

	if (!proc->query || !proc->query[0] || !proc->query[1])
		return (1);
	if (ft_strchr(proc->query[1], '=') == NULL)
	{
		str = set_get(proc->query[1]);
		if (ft_strcmp(str, "") != 0)
			env_set(proc->query[1], str);
		ft_strdel(&str);
	}
	else
	{
		arr = ft_strsplit_first_char(proc->query[1], '=');
		set(arr[0], arr[1]);
		env_set(arr[0], arr[1]);
		ft_mas_del(arr);
	}
	return (0);
}
