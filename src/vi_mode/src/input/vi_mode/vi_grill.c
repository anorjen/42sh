/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_grill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:09:28 by anorjen           #+#    #+#             */
/*   Updated: 2019/09/28 17:45:05 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

int	vi_grill(t_line *line, int count)
{
	char	*res;

	(void)count;
	ft_clear_line(line->len, line->left);
	res = str_new();
	res = str_addback(&res, "#", 1);
	line->str = str_union(&(line->str), res, 0);
	line->len += 1;
	free(res);
	write(1, line->str, line->len);
	return (KC_NL);
}
