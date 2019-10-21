/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 18:25:43 by anorjen           #+#    #+#             */
/*   Updated: 2019/09/28 15:38:56 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

int	vi_pipe(t_line *line, int count)
{
	int		i;

	ft_key_home(&(line->len), &(line->left));
	i = -1;
	count = (count > line->len ? line->len : count);
	while (++i < count)
		arrow_right(&(line->left));
	return (0);
}
