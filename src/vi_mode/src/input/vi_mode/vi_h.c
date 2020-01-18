/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_h.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:27:06 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 21:27:07 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

int	vi_h(t_line *line, int count)
{
	int		pos;

	pos = line->len - line->left;
	count = (count > pos ? pos : count);
	while (count--)
		arrow_left(line->len, &(line->left));
	return (0);
}
