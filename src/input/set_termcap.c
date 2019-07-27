/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_termcap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 18:51:43 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 16:23:14 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
}

char	*get_termcap(char **environ)
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

void	set_termcap(char **env)
{
	char	*termcap;

	termcap = get_termcap(env);
	if (termcap)
	{
		set_termenv(termcap);
	}
}
