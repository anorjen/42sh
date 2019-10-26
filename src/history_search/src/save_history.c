/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 19:12:52 by anorjen           #+#    #+#             */
/*   Updated: 2019/10/26 17:08:04 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "history_search.h"

#define HISTORY_FILE "~/.42sh_history"

int    save_history()
{
    int	        fd;
    char        *file;

    file = replace_dir(ft_strdup(HISTORY_FILE), g_sh->env);
	if ((fd = open(file, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH)) != -1)
	{

        g_h_session = list_rewind_to_begin(g_h_session);
        while (g_h_session->down)
        {
		    write(fd, g_h_session->line, ft_strlen(g_h_session->line));
            write(fd, "\n\n", 2);
            g_h_session = g_h_session->down;
        }
		close(fd);
		free(file);
		return (0);
	}
	free(file);
	return (-1);
}

