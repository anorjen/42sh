/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_arr_up.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 18:13:16 by anorjen           #+#    #+#             */
/*   Updated: 2019/09/28 15:39:55 by anorjen          ###   ########.fr       */
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
