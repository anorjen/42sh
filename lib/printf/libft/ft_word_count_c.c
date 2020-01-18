/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_count_c.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 14:53:48 by sbearded          #+#    #+#             */
/*   Updated: 2018/12/05 16:56:11 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_word_count_c(const char *s, char c)
{
	int		state;
	int		nw;
	int		i;

	state = 0;
	nw = 0;
	i = -1;
	while (s[++i] != '\0')
	{
		if (s[i] == c)
			state = 0;
		else if (state == 0)
		{
			state = 1;
			++nw;
		}
	}
	return (nw);
}
