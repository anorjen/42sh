/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eh_ft_undo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:01:31 by anorjen           #+#    #+#             */
/*   Updated: 2019/09/28 15:40:15 by anorjen          ###   ########.fr       */
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
