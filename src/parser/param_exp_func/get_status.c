/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:40:49 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:40:50 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_status(t_exp *exp)
{
	if (ft_strequ(exp->word, "") && ft_strequ(exp->param, ""))
		return (ft_itoa(g_sh->launch->status));
	else if (exp->param)
		return (ft_strdup(exp->env));
	else
	{
		parser_error_set("42sh: bad substitution");
		return (ft_strdup(" "));
	}
}
