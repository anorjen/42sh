/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcartwri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 13:12:32 by jcartwri          #+#    #+#             */
/*   Updated: 2019/10/27 13:16:50 by jcartwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias.h"

void	ft_strdel_alias_mas(char **mas)
{
	int i;

	i = 0;
	while (mas[i])
	{
		ft_strdel(&mas[i]);
		i++;
	}
	free(mas);
}

int		ms_alias(t_process *proc)
{
	char	*str;
	char	**mas;
	int		i;

	i = 0;
	if (proc->query[1] == NULL)
		alias_print();
	while (proc->query[++i])
	{
		if (ft_strchr(proc->query[i], '=') == NULL)
		{
			str = alias_get(proc->query[i]);
			if (ft_strcmp(str, "") != 0)
				ft_printf("%s%s%s\n", proc->query[1], "=", str);
			ft_strdel(&str);
		}
		else
		{
			mas = ft_strsplit(proc->query[i], '=');
			alias_set(mas[0], mas[1]);
			ft_strdel_alias_mas(mas);
		}
	}
	return (1);
}
