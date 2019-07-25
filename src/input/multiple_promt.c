/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_promt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 18:56:34 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/25 18:56:35 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void    multiple_promt(t_history_session *h_session, int mode)
{
    if (mode == MODE_QUOTE)
	{
		h_session->victor->push_back(&(h_session->victor), 0);
		print_ch(h_session, '\n', 0);
		ft_printf("%s", COMMAND_QUOTE);
	}
	if (mode == MODE_HEREDOC)
		ft_printf("heredoc> ");
    if (mode == MODE_PIPE)
    {
        h_session->victor->push_back(&(h_session->victor), 0);
		print_ch(h_session, '\n', 0);
		ft_printf("%s", "pipe> ");
    }
    if (mode == MODE_AND)
    {
        h_session->victor->push_back(&(h_session->victor), 0);
		print_ch(h_session, '\n', 0);
		ft_printf("%s", "cmdand> ");
    }
    if (mode == MODE_OR)
    {
        h_session->victor->push_back(&(h_session->victor), 0);
		print_ch(h_session, '\n', 0);
		ft_printf("%s", "cmdor> ");
    }
}
