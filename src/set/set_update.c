/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcartwri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 13:22:32 by jcartwri          #+#    #+#             */
/*   Updated: 2019/10/27 13:22:34 by jcartwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set.h"

static void	delete(void)
{
	unsigned int i;

	i = 0;
	if (g_set == NULL)
		return ;
	while (g_set[i] != NULL)
		ft_strdel(&(g_set[i++]));
	ft_memdel((void**)&g_set);
}

static char	*join(unsigned int i)
{
	char *ret;
	char *temp;

	temp = ft_strjoin("=", g_set_value->arr[i]);
	ret = ft_strjoin(g_set_key->arr[i], temp);
	ft_strdel(&temp);
	return (ret);
}

void		set_update(void)
{
	unsigned int i;

	delete();
	g_set = (char**)ft_memalloc(sizeof(char *) * (g_set_key->size + 1));
	if (g_set == NULL)
		exit(-1);
	i = 0;
	while (i < g_set_key->size)
	{
		g_set[i] = join(i);
		i++;
	}
	g_set[i] = NULL;
}
