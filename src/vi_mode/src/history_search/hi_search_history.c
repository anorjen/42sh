/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hi_search_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 15:58:08 by anorjen           #+#    #+#             */
/*   Updated: 2019/10/19 15:00:20 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hi_search_history.h"

void	ft_history_search(char *line)
{
	t_dlist	*tmp;
	char	*str;

	tmp = g_history;
	tmp = ft_dlist_rewind(tmp);
	write(1, "\n", 1);
	if (line && line[0] != '\0')
	{
		while (tmp)
		{
			str = ft_strstr(tmp->content, line);
			if (str)
			{
				write(1, tmp->content, tmp->content_size);
				write(1, "\n", 1);
			}
			tmp = tmp->next;
		}
	}
}

char	*ft_history_last(void)
{
	t_dlist	*tmp;

	tmp = g_history;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp->content);
}

char	*ft_history_word(char *word)
{
	t_dlist	*tmp;

	tmp = g_history;
	while (tmp->next)
		tmp = tmp->next;
	if (word && word[0] != '\0')
	{
		while (tmp)
		{
			if (ft_strncmp(tmp->content, word, ft_strlen(word)) == 0)
				return (tmp->content);
			tmp = tmp->prev;
		}
	}
	return (NULL);
}

char	*ft_history_number(int number)
{
	t_dlist	*tmp;
	int		i;

	tmp = g_history;
	i = 0;
	if (number >= 0)
	{
		tmp = ft_dlist_rewind(tmp);
		while (tmp && i++ < number)
			tmp = tmp->next;
		if (i == number)
			return (tmp->content);
	}
	else
	{
		number = (-1) * number;
		while (tmp->next)
			tmp = tmp->next;
		while (tmp && i++ < number)
			tmp = tmp->prev;
		if (i == number)
			return (tmp->content);
	}
	return (NULL);
}
