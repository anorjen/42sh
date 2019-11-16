/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:42:33 by mgorczan          #+#    #+#             */
/*   Updated: 2019/11/16 15:57:05 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "history_search.h"

int	save_history(void)
{
	int		fd;
	char	*file;
	char	*tmp;

	tmp = ft_strdup(HISTORY_FILE);
	file = replace_dir(tmp, g_sh->env);
	free(tmp);
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
