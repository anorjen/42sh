/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_promt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:59:47 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 21:59:48 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	multiple_promt(t_history_session *h_session, int mode)
{
	if (mode == MODE_QUOTE || mode == MODE_PIPE
				|| mode == MODE_AND || mode == MODE_OR || mode == MODE_MULTPL)
	{
		if (mode != MODE_MULTPL)
		{
			h_session->victor->push_back(&(h_session->victor), 0);
			print_ch(h_session, '\n');
		}
		if (mode == MODE_QUOTE)
			ft_printf("%s", COMMAND_QUOTE);
		else if (mode == MODE_PIPE)
			ft_printf("%s", "pipe> ");
		else if (mode == MODE_AND)
			ft_printf("%s", "cmdand> ");
		else if (mode == MODE_OR)
			ft_printf("%s", "cmdor> ");
		else if (mode == MODE_MULTPL)
			ft_printf("%s", "> ");
	}
	if (mode == MODE_HEREDOC)
		ft_printf("heredoc> ");
}
