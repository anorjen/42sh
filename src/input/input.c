/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 15:52:27 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/24 19:43:42 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static struct termios	stored_settings;


int		ft_readkey(int fd)
{
	int		ret;
	char	*b;
	int		res;
	int		i;

	b = ft_strnew(6);
	res = -1;
	if (b != NULL)
	{
		if ((ret = read(fd, &b[0], 6)) > 0)
		{
			res = b[0];
			if (b[0] == KEY_ESC && ret > 1)
			{
				i = 0;
				while (b[++i] != '\0')
					res += b[i];
				res += 1000;
			}
		}
		free(b);
	}
	return (res);
}

void	key_func(t_history_session *h_session, int key)
{
	if (key == KEY_BS)
		backspace_ch(h_session);
	else if (key == KEY_LEFT)
		left_ch(h_session);
	else if (key == KEY_RIGHT)
		right_ch(h_session);
	else if (key < 255 && key >= 32)
		print_ch(h_session, key, 1);
	else if (key == KEY_SHIFT_UP || key == KEY_SHIFT_DOWN)
		navigation_line(h_session, key);
	else if (key == KEY_HOME || key == KEY_END)
		key_endhome(h_session, key);
	else if (key == KEY_SHIFT_LEFT || key == KEY_SHIFT_RIGHT)
		navigation_words(h_session, key);
	else if (key == KEY_PASTE && g_buffer)
		key_paste(h_session);
}

int		key_entr(t_history_session *h_session, int key)
{
	if (h_session->line && h_session->line[0] == '\0')
	{
		free(h_session->line);
		h_session->line = NULL;
	}
	while (h_session->victor->curr_arr < (h_session->victor->lenght - 1))
	{
		h_session->victor->curr_arr++;
		tputs(term->do_, 1, putchar_);
	}
	write(1, "\n", 1);
	return (1);
}

int		key_control_c(t_history_session *h_session)
{
	while (h_session->victor->curr_arr < (h_session->victor->lenght - 1))
	{
		h_session->victor->curr_arr++;
		tputs(term->do_, 1, putchar_);
	}
	if (h_session->line)
		free(h_session->line);
	h_session->line = NULL;
	return (1);
}

int		is_delim(char ch)
{
	if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || ch == '\v')
		return (1);
	return (0);
}

void	set_keypress(void)
{
	struct termios	new_settings;

	tcgetattr(0, &stored_settings);
	new_settings = stored_settings;
	new_settings.c_lflag &= (~ICANON & ~ECHO);
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &new_settings);
}

void	reset_keypress(void)
{
	tcsetattr(0, TCSANOW, &stored_settings);
	return;
}

char		*get_termcap(char **environ)
{
	char	*term;
	char	*term_edit;
	
	if ((term = ft_strnew(2048)))
	{
		if ((term_edit = ft_strdup(getenv("TERM"))))
		{
			tgetent(term, term_edit);
			if (tgetent(term, term_edit) == 1)
			{
				free(term_edit);
				return (term);
			}
			free(term_edit);
		}
		free(term);
	}
	return (NULL);
}

void	set_termenv(char *termcap)
{
	term = (t_term *)malloc(sizeof(t_term));
	term->le = tgetstr("le", &termcap);
	term->nd = tgetstr("nd", &termcap);
	term->cd = tgetstr("cd", &termcap);
	term->dc = tgetstr("dc", &termcap);
	term->im = tgetstr("im", &termcap);
	term->ei = tgetstr("ei", &termcap);
	term->so = tgetstr("so", &termcap);
	term->se = tgetstr("se", &termcap);
	term->up = tgetstr("up", &termcap);
	term->do_ = tgetstr("do", &termcap);


}






char	*input(t_history_session **h_session, int lenght_hello, int mode, char **env)
{
	int		key;
	int		temp;
	char	*termcap;


	if ((termcap = get_termcap(env)))
		set_termenv(termcap);
	set_keypress();

	temp = 1;
	(*h_session)->lenght_hello = 1 + lenght_hello;
	if (mode == COMMANDID_QUOTE)
	{
		(*h_session)->victor->push_back(&((*h_session)->victor), 0);
		print_ch(*h_session, '\n', 0);
		ft_printf("%s", COMMAND_QUOTE);
	}
	if (mode == MODE_HEREDOC)
	{
		ft_printf("heredoc ");
	}
	(*h_session)->fl = mode ? 1 : 0;

	while (21)
	{
		key = ft_readkey(0);
		if (key == -1 && key_control_c(*h_session))
			break ;
		if (key == KEY_COPY_LEFT || key == KEY_COPY_RIGHT)
		{
			temp = 0;
			key_cop(*h_session, key);
		}
		else if (!temp)
		{
			temp = !g_dispersion ? 1 : g_dispersion;
			if (key == KEY_CUT && g_dispersion)
				key_cut(*h_session, temp);
			else if (g_dispersion)
				save_buff(*h_session);
		}
		if (key == KEY_NL && key_entr(*h_session, key))
			break ;
		if (mode != MODE_HEREDOC && (key == KEY_UP || key == KEY_DOWN) && !(*h_session)->fl)
			key_history(*h_session, key);
		else
			(*h_session)->number_hist = 0;
		key_func(*h_session, key);
	}
	(*h_session)->victor->curr_arr = (*h_session)->victor->lenght - 1;
	(*h_session)->left = (*h_session)->lenght;
	(*h_session)->fl = 0;
	reset_keypress();
	free(termcap);
	free(term);
	return ((*h_session)->lenght == 0 ? NULL : ft_strdup((*h_session)->line));
}
