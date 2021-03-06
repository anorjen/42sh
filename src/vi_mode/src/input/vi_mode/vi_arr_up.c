/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_arr_up.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:25:46 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:25:48 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

int	vi_arr_up(t_line *line, int count)
{
	int		i;

	(void)count;
	ft_key_home(&(line->len), &(line->left));
	i = 0;
	while (i < line->len && (line->str)[i] == ' ')
	{
		arrow_right(&(line->left));
		++i;
	}
	return (0);
}
