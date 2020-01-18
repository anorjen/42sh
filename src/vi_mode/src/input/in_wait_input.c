/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_wait_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:15:17 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 21:15:19 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

int			is_str(char *str)
{
	int	i;

	if (str)
	{
		i = -1;
		while (str[++i])
		{
			if (str[i] != ' ')
				return (1);
		}
	}
	return (0);
}

void		add_str_history(t_line *line, int key)
{
	t_dlist	*elem;

	if (!line->edit_history ||
	(!ft_strequ(line->edit_history->content, line->str) && key != KC_CTRL_U))
	{
		elem = ft_dlist_new(line->str, line->len);
		ft_dlist_add(&(line->edit_history), elem);
	}
}

t_line		*line_init(void)
{
	t_line	*line;

	line = (t_line *)malloc(sizeof(t_line));
	line->str = str_new();
	line->len = 0;
	line->left = 0;
	line->edit_history = NULL;
	return (line);
}

void		line_deinit(t_line *line)
{
	free(line->str);
	ft_dlist_del(&(line->edit_history));
	free(line);
}

char		*wait_input(void)
{
	t_line	*line;
	char	*str;

	set_keypress();
	line = line_init();
	if (g_input_mode == 1)
		line = wait_input_vi(line);
	else if (g_input_mode == 2)
		line = wait_input_rl(line);
	str = ft_strdup(line->str);
	line_deinit(line);
	reset_keypress();
	return (str);
}
