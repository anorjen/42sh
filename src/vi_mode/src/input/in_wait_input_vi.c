/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_wait_input_vi.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:15:44 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 21:15:46 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

static t_vi_actions	g_vi_actions[41] = {
	{vi_grill, '#'},
	{vi_l, ' '},
	{vi_v, 'v'},
	{vi_j, 'j'},
	{vi_k, 'k'},
	{vi_l, 'l'},
	{vi_h, 'h'},
	{vi_w, 'w'},
	{vi_w, 'W'},
	{vi_e, 'e'},
	{vi_e, 'E'},
	{vi_b, 'b'},
	{vi_b, 'B'},
	{vi_arr_up, '^'},
	{vi_dollar, '$'},
	{vi_zero, '0'},
	{vi_pipe, '|'},
	{vi_f, 'f'},
	{vi_fb, 'F'},
	{vi_semicolon, ';'},
	{vi_comma, ','},
	{vi_a, 'a'},
	{vi_ab, 'A'},
	{vi_i, 'i'},
	{vi_ib, 'I'},
	{vi_r, 'r'},
	{vi_i, 'R'},
	{vi_c, 'c'},
	{vi_cb, 'C'},
	{vi_sb, 'S'},
	{vi_x, 'x'},
	{vi_xb, 'X'},
	{vi_d, 'd'},
	{vi_db, 'D'},
	{vi_y, 'y'},
	{vi_yb, 'Y'},
	{vi_p, 'p'},
	{vi_pb, 'P'},
	{vi_u, 'u'},
	{vi_ub, 'U'},
	{NULL, 0}
};

int			vi_do_command(t_line *line, char cmnd, int count)
{
	int	i;
	int	key;

	count = (count <= 0 ? 1 : count);
	i = 0;
	while (g_vi_actions[i].action != NULL)
	{
		if (cmnd == g_vi_actions[i].value)
		{
			key = g_vi_actions[i].action(line, count);
			return (key);
		}
		++i;
	}
	return (-1);
}

static int	ft_comcount(unsigned char *b)
{
	int	count;
	int	ret;

	count = 0;
	if (*b != '0')
	{
		while (ft_isdigit(*b))
		{
			count = 10 * count + (*b - '0');
			ret = read(0, b, 1);
		}
	}
	return (count);
}

int			vi_command(t_line *line)
{
	int				ret;
	unsigned char	b[6];
	int				res;
	int				i;
	int				count;

	ft_memset(b, 0, sizeof(b));
	res = 0;
	if ((ret = read(0, &b[0], 6)) > 0)
	{
		if (!ft_isprint(b[0]))
		{
			i = -1;
			while (++i < ret)
				res += b[i];
			res += (ret > 1 ? 1000 : 0);
		}
		else
		{
			count = ft_comcount(&b[0]);
			res = vi_do_command(line, b[0], count);
		}
	}
	return (res);
}

t_line		*wait_input_vi(t_line *line)
{
	int				key;
	int				com_state;

	com_state = 0;
	while (1)
	{
		key = (com_state == 0 ? ft_read_keycode(1, line) : vi_command(line));
		if (key == KC_ESC || key == 'i')
			com_state = (key == KC_ESC ? 1 : 0);
		else if (key == KC_TAB)
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
			keycode_func(key, line);
		add_str_history(line, key);
	}
	return (line);
}
