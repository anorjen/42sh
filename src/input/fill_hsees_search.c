/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_hsees_search.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <anorjen@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 20:27:23 by mgorczan          #+#    #+#             */
/*   Updated: 2019/11/30 18:35:34 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_history_session	*crt_hsess(void)
{
	t_history_session *h_session;

	h_session = (t_history_session*)malloc(sizeof(t_history_session));
	if (!h_session)
		exit(1);
	return (h_session);
}

char				*ft_strjoin_pro(char *str1, char *str2)
{
	char *temp;

	temp = str1;
	str1 = ft_strjoin(str1, str2);
	free(temp);
	return (str1);
}

t_history_session	*add_hsess_search(t_history_session *h_session,
									char *line, int lenght_hello)
{
	if (h_session)
	{
		h_session->line = ft_strjoin_pro(h_session->line, "\n");
		h_session->line = ft_strjoin_pro(h_session->line, line);
		h_session->lenght = ft_strlen(h_session->line);
		h_session->left = h_session->lenght;
		h_session->victor->push_back(&(h_session->victor), ft_strlen(line) + 1);
	}
	else
	{
		h_session = crt_hsess();
		h_session->up = NULL;
		h_session->down = NULL;
		h_session->number_hist = 0;
		g_buffer = NULL;
		g_dispersion = 0;
		init_verb(h_session, lenght_hello);
		h_session->line = ft_strdup(line);
		h_session->lenght = ft_strlen(line);
		h_session->left = h_session->lenght;
		h_session->victor->array[h_session->victor->curr_arr] =
			h_session->lenght;
	}
	return (h_session);
}

t_history_session	*initsrch_loop(int fd, int lenght_hello)
{
	t_history_session	*h_session;
	char				*line;

	h_session = NULL;
	while (get_next_line(fd, &line))
	{
		if (ft_strcmp(line, ""))
			h_session = add_hsess_search(h_session, line, lenght_hello);
		else
		{
			free(line);
			if (get_next_line(fd, &line))
			{
				h_session->down =
					add_hsess_search(h_session->down, line, lenght_hello);
				h_session->down->up = h_session;
				h_session = h_session->down;
			}
		}
		free(line);
	}
	free(line);
	return (h_session);
}

t_history_session	*init_search_history(int lenght_hello)
{
	int					fd;
	char				*file;

	g_h_session = NULL;
	file = replace_dir(ft_strdup(HISTORY_FILE), g_sh->env);
	fd = open(file, O_RDONLY);
	if (fd != -1)
	{
		g_h_session = initsrch_loop(fd, lenght_hello);
		close(fd);
	}
	return (g_h_session);
}
