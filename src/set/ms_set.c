/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 13:21:00 by rwalder-          #+#    #+#             */
/*   Updated: 2019/11/23 18:09:43 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set.h"

char		*ft_add_begin_end(char *str, char *new)
{
	char *s;
	char *add;

	if (str == NULL || new == NULL || str[0] == '\0' || new[0] == '\0')
	{
		return (NULL);
	}
	if (ft_strlen(new) == 1)
	{
		s = ft_strjoin(new, str);
		add = ft_strjoin(s, new);
		ft_strdel(&s);
	}
	else
	{
		s = ft_strjoin(new, str);
		add = ft_strjoin(s, "' )");
		ft_strdel(&s);
	}
	return (add);
}

void		ft_mas_del(char **mas)
{
	int i;

	i = -1;
	while (mas && mas[++i])
	{
		ft_strdel(&mas[i]);
	}
	free(mas);
}

char		**ft_strsplit_first_char(char *str, char c)
{
	char	**arr;
	char	*s;
	int		len;
	int		i;

	i = 0;
	if (ft_strchr(str, c) == 0)
	{
		return (NULL);
	}
	arr = (char **)malloc(sizeof(char *) * 3);
	len = ft_strlen(str);
	while (str[i] != '\0' && str[i] != c)
	{
		i++;
	}
	arr[0] = ft_strsub(str, 0, i);
	s = ft_strsub(str, i + 1, len - i - 1);
	if (ft_strchr(s, c) != 0)
	{
		s = ft_add_begin_end(s, "'");
	}
	arr[1] = s;
	arr[2] = NULL;
	return (arr);
}

static void	set_mode(char *command)
{
	if (!ft_strcmp(command, "readline"))
	{
		ft_printf("readline mode\n");
		g_input_mode = 2;
	}
	else
	{
		if (!ft_strcmp(command, "vi"))
		{
			ft_printf("vi mode\n");
			g_input_mode = 1;
		}
		else
		{
			ft_printf("default mode\n");
			g_input_mode = 0;
		}
	}
}

int			ms_set(t_process *proc)
{
	if (proc->query[1] == NULL)
	{
		set_print(proc);
	}
	else
	{
		if (proc->query[0] && proc->query[1] && proc->query[2]
				&& !ft_strcmp("-o", proc->query[1]))
		{
			set_mode(proc->query[2]);
		}
	}
	return (0);
}
