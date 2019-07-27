/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_cut.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 16:33:26 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/27 15:12:15 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void		keep_left(t_history_session *h_session)
{
	int i;

	i = h_session->left - 1;
	tputs(term->cd, 1, putchar_);
	while (i >= 0 && h_session->line[i] && h_session->line[i] != '\n')
	{
		tputs(term->le, 1, putchar_);
		--i;
	}
	tputs(term->cd, 1, putchar_);
	while (h_session->victor->curr_arr)
	{
		tputs(term->up, 1, putchar_);
		i = 0;
		h_session->victor->curr_arr--;
		while (!h_session->victor->curr_arr && ++i < h_session->lenght_hello)
			tputs(term->nd, 1, putchar_);
		tputs(term->cd, 1, putchar_);
	}
}

void		ct_line(t_history_session *h_session, int disp)
{
	if (disp < 0)
	{
		cut_str(&(h_session->line),
			h_session->left, h_session->left + -1 * disp);
		write_vector(h_session);
		tputs(term->cd, 1, putchar_);
		ft_printf("%s", &h_session->line[h_session->left]);
	}
	else if (disp > 0)
	{
		keep_left(h_session);
		cut_str(&(h_session->line), h_session->left - disp, h_session->left);
		write_vector(h_session);
		ft_printf("%s", h_session->line);
		h_session->left -= disp;
	}
}

void		key_cut(t_history_session *h_session, int disp)
{
	int i;
	int temp;

	tputs(term->im, 1, putchar_);
	ct_line(h_session, disp);
	temp = h_session->lenght;
	while (temp > h_session->left)
	{
		if (h_session->line[temp - 1] == '\n')
		{
			h_session->victor->curr_arr--;
			tputs(term->up, 1, putchar_);
			i = !h_session->victor->curr_arr ? -h_session->lenght_hello : 0;
			while (++i < h_session->victor->array[h_session->victor->curr_arr])
				tputs(term->nd, 1, putchar_);
		}
		else
			tputs(term->le, 1, putchar_);
		temp--;
	}
	g_dispersion = 0;
	tputs(term->ei, 1, putchar_);
}
