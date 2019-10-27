/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 15:58:08 by anorjen           #+#    #+#             */
/*   Updated: 2019/10/26 16:12:03 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history_search.h"

void	search_all_str(t_history_session *h_session, char *line)
{
	t_history_session	*tmp;
	char				*str;

	tmp = h_session;
	tmp = list_rewind_to_begin(tmp);
	write(1, "\n", 1);
	if (line && line[0] != '\0')
	{
		while (tmp->down)
		{
			str = ft_strstr(tmp->line, line);
			if (str)
			{
				write(1, tmp->line, ft_strlen(tmp->line));
				write(1, "\n", 1);
			}
			tmp = tmp->down;
		}
	}
	h_session->line[0] = '\0';
	key_entr(h_session);
}

void	search_last(t_history_session *h_session)
{
	t_history_session	*tmp;

	tmp = h_session;
	tmp = list_rewind_to_end(tmp);
	write(1, "\n", 1);
	write(1, tmp->up->line, ft_strlen(tmp->up->line));
	h_session->line[0] = '\0';
	key_entr(h_session);
}

void	search_word(t_history_session *h_session, char *word)
{
	t_history_session	*tmp;

	tmp = h_session;
	tmp = list_rewind_to_end(tmp);
	if (tmp->up)
		tmp = tmp->up;
	write(1, "\n", 1);
	if (word && word[0] != '\0')
	{
		while (tmp)
		{
			if (ft_strstr(tmp->line, word) != NULL)
			{
				write(1, tmp->line, ft_strlen(tmp->line));
				write(1, "\n", 1);
			}
			tmp = tmp->up;
		}
	}
	h_session->line[0] = '\0';
	key_entr(h_session);
}

void	search_number(t_history_session *h_session, int number)
{
	t_history_session	*tmp;
	int					i;

	tmp = h_session;
	write(1, "\n", 1);
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
		write(1, tmp->line, ft_strlen(tmp->line));
	h_session->line[0] = '\0';
	key_entr(h_session);
}
