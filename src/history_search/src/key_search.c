/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 16:42:58 by anorjen           #+#    #+#             */
/*   Updated: 2019/10/26 16:47:35 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "history_search.h"

void	key_search(t_history_session *h_session)
{
	char	*line;
	int		len;
	int		i;

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
				search_last(h_session);
			else if ((line[i + 1] >= 48 && line[i + 1] <= 57)
						|| line[i + 1] == '-')
				search_number(h_session, ft_atoi(&line[i + 1]));
			else
				search_word(h_session, &line[i + 1]);
		}
		else
			search_all_str(h_session, line);
	}
}
