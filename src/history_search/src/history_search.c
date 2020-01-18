/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <anorjen@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:42:22 by sbearded          #+#    #+#             */
/*   Updated: 2019/11/30 20:45:54 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history_search.h"

t_history_session	*search_all_str(t_history_session *h_session)
{
	t_history_session			*tmp;

	if (!(tmp = h_session) || !h_session->line || h_session->line[0] == '\0')
		return (NULL);
	if (g_old_search &&
		ft_strcmp(g_old_search->line, h_session->line) == 0 && g_search_word)
		tmp = g_old_search;
	else
	{
		if (g_search_word)
			free(g_search_word);
		tmp = list_rewind_to_end(tmp);
		g_search_word = ft_strdup(h_session->line);
	}
	while ((tmp = tmp->up))
	{
		if (ft_strstr(tmp->line, g_search_word))
		{
			g_old_search = tmp;
			return (tmp);
		}
	}
	g_old_search = NULL;
	return (NULL);
}

t_history_session	*search_last(t_history_session *h_session)
{
	t_history_session	*tmp;

	tmp = h_session;
	tmp = list_rewind_to_end(tmp);
	tmp = tmp->up;
	return (tmp);
}

t_history_session	*search_word(t_history_session *h_session, char *word)
{
	t_history_session	*tmp;

	tmp = h_session;
	tmp = list_rewind_to_end(tmp);
	if (tmp->up)
		tmp = tmp->up;
	if (word && word[0] != '\0')
	{
		while (tmp)
		{
			if (ft_strstr(tmp->line, word) != NULL)
			{
				return (tmp);
			}
			tmp = tmp->up;
		}
	}
	return (NULL);
}

t_history_session	*search_number(t_history_session *h_session, int number)
{
	t_history_session	*tmp;
	int					i;

	tmp = h_session;
	i = 0;
	if (number >= 0)
	{
		tmp = list_rewind_to_begin(tmp);
		while (tmp && ++i < number)
			tmp = tmp->down;
	}
	else
	{
		number = (-1) * number;
		tmp = list_rewind_to_end(tmp);
		if (tmp->up)
			tmp = tmp->up;
		while (tmp && ++i < number)
			tmp = tmp->up;
	}
	if (i == number)
		return (tmp);
	return (NULL);
}
