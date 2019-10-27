/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assist_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 17:14:11 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 15:12:15 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int					putchar_(int c)
{
	write(1, &c, 1);
	return (0);
}

void				cut_str(char **comm, int i, int lenght)
{
	char *temp;
	char *temp2;

	if (!comm || !(*comm))
		return ;
	temp = ft_strsub(*comm, 0, i);
	temp2 = ft_strsub(*comm, lenght, ft_strlen(*comm));
	free(*comm);
	*comm = ft_strjoin(temp, temp2);
	free(temp);
	free(temp2);
}

void				write_vector(t_history_session *h_session)
{
	int i;
	int j;

	h_session->victor->del(&(h_session->victor));
	h_session->victor = init_vector();
	i = 0;
	j = 0;
	h_session->lenght = 0;
	while (h_session->line[i])
	{
		if (h_session->line[i] == '\n')
		{
			h_session->victor->push_back(&(h_session->victor), j);
			j = 0;
		}
		i++;
		++j;
		h_session->lenght++;
	}
	h_session->victor->push_back(&(h_session->victor), j);
}

static void			init_verb(t_history_session *h_session, int lenght_hello)
{
	h_session->left = 0;
	h_session->lenght = 0;
	h_session->line = NULL;
	h_session->down = NULL;
	h_session->victor = init_vector();
	h_session->victor->push_back(&h_session->victor, 0);
	h_session->number_hist = 0;
	h_session->fl = 0;
	h_session->lenght_hello = 1 + lenght_hello;
}

t_history_session *add_hsess_search(t_history_session *h_session, char *line, int lenght_hello)
{
	if (h_session)
	{
		h_session->line = ft_strjoin(h_session->line, "\n");
		h_session->line = ft_strjoin(h_session->line, line);
		h_session->lenght = ft_strlen(h_session->line);
		h_session->left = h_session->lenght;
		h_session->victor->push_back(&(h_session->victor), ft_strlen(line + 1));
	}
	else
	{
		if ((h_session =
		(t_history_session*)malloc(sizeof(t_history_session))) == NULL)
			exit(1);
		h_session->up = NULL;
		h_session->number_hist = 0;
		g_buffer = NULL;
		g_dispersion = 0;
		init_verb(h_session, lenght_hello);
		h_session->line = ft_strdup(line);
		h_session->lenght = ft_strlen(line);
		h_session->left = h_session->lenght;
		h_session->victor->array[h_session->victor->curr_arr] = h_session->lenght;
	}
	return (h_session);
}

t_history_session	*init_search_history(int lenght_hello)
{
	int fd;
	t_history_session *h_session;
	char *line;

	h_session = NULL;
	fd = open("/Users/mgorczan/.42sh_history", O_RDONLY); // super crutch
	if (fd != -1)
	{
		while (get_next_line(fd, &line))
		{
			if (ft_strcmp(line, ""))
			{
				h_session = add_hsess_search(h_session, line, lenght_hello);
				close(fd);
				break ;
			}
			else
			{

			}
			free(line);
		}
		// ft_printf("%s %i %i %i %i\n", h_session->line, h_session->lenght, h_session->left, h_session->victor->array[h_session->victor->curr_arr], h_session->victor->curr_arr);
		// if ((h_session =
		// (t_history_session*)malloc(sizeof(t_history_session))) == NULL)
		// 	exit(1);

		close(fd);
		// exit(0);
	}
	else if ((h_session =
		(t_history_session*)malloc(sizeof(t_history_session))) == NULL)
			exit(1);
	return (h_session);
	
}



t_history_session	*add_history(t_history_session *h_session, int lenght_hello)
{
	t_history_session *temp;

	if (!h_session)
	{
		// h_session = init_search_history(lenght_hello);
		if ((h_session =
		(t_history_session*)malloc(sizeof(t_history_session))) == NULL)
			exit(1);
		h_session->up = NULL;
		h_session->number_hist = 0;
		g_buffer = NULL;
		g_dispersion = 0;
	}
	else if (h_session->line)
	{
		if ((h_session->down =
		(t_history_session*)malloc(sizeof(t_history_session))) == NULL)
			exit(1);
		temp = h_session;
		h_session = h_session->down;
		h_session->up = temp;
	}
	else if (!h_session->line)
		h_session->victor->del(&h_session->victor);
	init_verb(h_session, lenght_hello);
	
	return (h_session);
}
