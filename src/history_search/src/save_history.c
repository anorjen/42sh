/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 19:12:52 by anorjen           #+#    #+#             */
/*   Updated: 2019/10/19 19:45:13 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "history_search.h"

#define TMP_FILE "~/.42sh_history"

int    save_history()
{
    extern char **environ;
    int	        fd;
    char        *file;

    file = replace_dir(ft_strdup(TMP_FILE), environ);
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
		return (0);
	}
	return (-1);
}

