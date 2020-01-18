/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_u.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:28:55 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 21:28:56 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

int		vi_u(t_line *line, int count)
{
	++count;
	ft_undo(line);
	return (0);
}

int		vi_ub(t_line *line, int count)
{
	t_dlist	*tmp;

	++count;
	if (line->str && (line->str)[0] != '\0')
	{
		tmp = line->edit_history;
		ft_clear_line(line->len, line->left);
		line->len = 0;
		line->left = 0;
		free(line->str);
		line->str = str_new();
		if (tmp->next)
		{
			while (tmp->next)
				tmp = tmp->next;
			write(1, tmp->content, tmp->content_size);
			line->str = str_addback(&(line->str), tmp->content,
													tmp->content_size);
			line->len = tmp->content_size;
		}
		ft_dlist_del(&(line->edit_history));
	}
	return (0);
}
