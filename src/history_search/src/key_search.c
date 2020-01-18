/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:42:26 by mgorczan          #+#    #+#             */
/*   Updated: 2019/11/16 18:57:47 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "history_search.h"

static void	print_command(t_history_session *h_session,
		t_history_session *result)
{
	if (h_session != NULL && result != NULL)
	{
		clear_line(h_session);
		(h_session->number_hist)++;
		free(h_session->line);
		h_session->line = ft_strdup(result->line);
		h_session->left = result->left;
		h_session->lenght = result->lenght;
		h_session->victor->del(&(h_session->victor));
		h_session->victor = result->victor->copy(result->victor);
		ft_printf("%s", h_session->line);
	}
}

void		key_search(t_history_session *h_session)
{
	char				*line;
	int					len;
	int					i;
	t_history_session	*result;

	line = h_session->line;
	len = h_session->lenght;
	i = 0;
	if (line != NULL && line[0] != '\0' && line[0] != '\n')
	{
		while ((line[i] == ' ' || line[i] == '\t') && i < len)
			++i;
		if (line[i] == '!' && (i + 1) < len)
		{
			if (line[i + 1] == '!')
				result = search_last(h_session);
			else if ((line[i + 1] >= 48 && line[i + 1] <= 57)
						|| line[i + 1] == '-')
				result = search_number(h_session, ft_atoi(&line[i + 1]));
			else
				result = search_word(h_session, &line[i + 1]);
		}
		else
			result = search_all_str(h_session);
		print_command(h_session, result);
	}
}
