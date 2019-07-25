/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kazekage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 14:11:36 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/25 14:11:37 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void		kazekage(char **arg)
{
	t_job	*job;
    char    **segment_arg;
	int     mode;
    int		status;
	
	status = 0;
    mode = 0;
    while (arg)
    {
	    job = lexer(arg);
    }

}
