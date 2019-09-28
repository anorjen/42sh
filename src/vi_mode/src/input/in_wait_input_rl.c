/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_wait_input_rl.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 16:44:20 by anorjen           #+#    #+#             */
/*   Updated: 2019/09/28 18:01:02 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

static void	keycode_func_rl(int key, t_line *line)
{
	if (key == KC_BS)
		ft_backspace(&(line->str), &(line->len), line->left);
	else if (key == KC_CTRL_E)
		ft_copy_mode(line);
	else if (key == RL_CTRL__)
		ft_undo(line);
	else if (key == RL_CTRL_T)
		ft_swap_chars(line);
	else if (key == RL_ALT_T)
		ft_swap_words(line);
	else if (key == KC_CTRL_D && line->len == 0)
		exit(0);
	else
		ft_keys(key, &(line->str), &(line->len), &(line->left));
}

t_line			*wait_input_rl(t_line *line)
{
	int	key;

	key = 0;
	while (1)
	{
		key = ft_read_keycode(1, line);
		if (key == KC_TAB)
			continue ;
		else if (key == KC_NL || key == KC_CTRL_R)
		{
			if (key == KC_NL)
				ft_newline(line);
			else if (key == KC_CTRL_R)
				ft_history_search(line->str);
			break ;
		}
		else
			keycode_func_rl(key, line);
		add_str_history(line, key);
	}
	return (line);
}
