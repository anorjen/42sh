/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eh_ft_undo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:13:11 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 21:13:14 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

void	ft_undo(t_line *line)
{
	if (line->str && (line->str)[0] != '\0')
	{
		ft_clear_line(line->len, line->left);
		line->len = 0;
		line->left = 0;
		free(line->str);
		line->str = str_new();
		if (line->edit_history->next)
		{
			line->edit_history = line->edit_history->next;
			write(1, line->edit_history->content,
											line->edit_history->content_size);
			line->str = str_addback(&(line->str), line->edit_history->content,
											line->edit_history->content_size);
			line->len = line->edit_history->content_size;
		}
		else
			ft_dlist_del(&(line->edit_history));
	}
}
