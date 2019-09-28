/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_w.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 17:52:05 by anorjen           #+#    #+#             */
/*   Updated: 2019/09/28 15:38:48 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

int	vi_w(t_line *line, int count)
{
	while (count-- && line->left > 0)
		ft_key_next(line->str, line->len, &(line->left));
	return (0);
}
