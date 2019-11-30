/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:42:30 by mgorczan          #+#    #+#             */
/*   Updated: 2019/11/30 18:08:07 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "history_search.h"

static void	print_recursive(t_history_session *tmp, t_fc *fc)
{
	int					len;
	int					i;

	len = listlen(tmp);
	tmp = list_rewind_to_end(tmp);
	if (fc->num <= 0 || len <= fc->num)
		fc->num = len + 1;
	i = -1;
	while (++i < fc->num && tmp)
	{
		if (!(fc->n))
			ft_printf("%5d  %s\n", len - i, tmp->line);
		else
			ft_printf("%s\n", tmp->line);
		tmp = tmp->up;
	}
}

static void	print_direct(t_history_session *tmp, t_fc *fc)
{
	int					len;
	int					i;

	len = listlen(tmp);
	if (fc->num <= 0 || len <= fc->num)
	{
		tmp = list_rewind_to_begin(tmp);
		fc->num = len;
	}
	else
	{
		tmp = list_rewind_to_end(tmp);
		i = fc->num;
		while (--i)
			tmp = tmp->up;
	}
	while (tmp)
	{
		if (!(fc->n))
			ft_printf("%5d  %s\n", len - --(fc->num), tmp->line);
		else
			ft_printf("%s\n", tmp->line);
		tmp = tmp->down;
	}
}

void		print_history(t_history_session *h_session, t_fc *fc)
{
	t_history_session	*tmp;

	tmp = h_session;
	if (fc->r)
		print_recursive(tmp, fc);
	else
		print_direct(tmp, fc);
}
