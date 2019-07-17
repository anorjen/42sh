/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assist_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 17:14:11 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/13 17:14:12 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"


void _commas(t_history_session *h_session, int key)
{

	if ((key == '\"' || key == '\'') && (h_session->comm.fd % 2 == 0))
	{
		++(h_session->comm.fd);
		h_session->comm.ch = key;
	}
	else if (key == h_session->comm.ch  && h_session->comm.fd % 2 != 0)
		++(h_session->comm.fd);
}

int	putchar_(int c)
{
	write(1, &c, 1);
	return (0);
}

void	cut_str(char **comm, int i, int lenght)
{
	char *temp;
	char *temp2;

	if (!comm || !(*comm))
		return ;
	temp = ft_strsub(*comm, 0, i);
	temp2 = ft_strsub(*comm, lenght, ft_strlen(*comm));
	free(*comm);
	*comm = ft_strjoin(temp, temp2);
	free(temp);
	free(temp2);
}