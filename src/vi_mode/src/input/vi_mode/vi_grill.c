/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_grill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:26:59 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 21:27:00 by sbearded         ###   ########.fr       */
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
