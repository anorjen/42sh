/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 15:40:29 by anorjen           #+#    #+#             */
/*   Updated: 2019/10/26 16:53:52 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "history_search.h"

static void	print_all(t_history_session *h_session, int n)
{
	t_history_session	*tmp;
	int					i;

	i = 0;
	tmp = h_session;
	tmp = list_rewind_to_begin(tmp);
	while (tmp->down != NULL)
	{
		if (!n)
			ft_printf("%5d  %s\n", ++i, tmp->line);
		else
			ft_printf("%s\n", tmp->line);
		tmp = tmp->down;
	}
}

static void	print_last(t_history_session *h_session, int num, int n)
{
	int					len;
	int					i;
	t_history_session	*tmp;

	len = listlen(h_session);
	if (len <= num)
		print_all(h_session, n);
	else
	{
		tmp = h_session;
		tmp = list_rewind_to_end(tmp);
		i = num;
		while (i--)
			tmp = tmp->up;
		while (num--)
		{
			if (!n)
				ft_printf("%5d  %s\n", len - num, tmp->line);
			else
				ft_printf("%s\n", tmp->line);
			tmp = tmp->down;
		}
	}
}

void		print_history(t_history_session *h_session, int num, int n)
{
	if (num == 0)
		print_all(h_session, n);
	else
		print_last(h_session, num, n);
}
