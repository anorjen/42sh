/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_wait_input_default.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:15:27 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:15:29 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

void	listener(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	sh_print_promt();
}

void	ft_print(t_line *line, char c)
{
	int			pos;
	char		*buf;

	pos = line->len - line->left;
	buf = str_substr(line->str, pos, line->left);
	(line->str)[pos] = '\0';
	line->str = str_addback(&(line->str), &c, 1);
	line->str = str_addback(&(line->str), buf, line->len - pos);
	free(buf);
	(line->len)++;
	tputs(g_term->im, 1, ft_put);
	write(1, &c, 1);
	tputs(g_term->ei, 1, ft_put);
}

int		ft_read_keycode(int pm, t_line *line)
{
	int				ret;
	unsigned char	b[6];
	int				res;
	int				i;

	ft_memset(b, 0, sizeof(b));
	res = 0;
	i = -1;
	if ((ret = read(0, &b[0], 6)) > 0)
	{
		if (!ft_isprint(b[0]))
		{
			while (++i < ret)
				res += b[i];
			res += (ret > 1 ? 1000 : 0);
		}
		else if (pm)
		{
			while (++i < ret)
				ft_print(line, b[i]);
		}
	}
	return (res);
}

void	keycode_func(int key, t_line *line)
{
	if (key == KC_BS)
		ft_backspace(&(line->str), &(line->len), line->left);
	else if (key > 1000)
		ft_keys(key, &(line->str), &(line->len), &(line->left));
	else if (key == KC_CTRL_E)
		ft_copy_mode(line);
	else if (key == KC_CTRL_U)
		ft_undo(line);
	else if (key == KC_CTRL_D && line->len == 0)
		exit(0);
}

t_line	*wait_input_default(t_line *line)
{
	int				key;

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
			keycode_func(key, line);
		add_str_history(line, key);
	}
	return (line);
}
