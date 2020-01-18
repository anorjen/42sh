/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_sb.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:28:41 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 21:28:42 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

int		vi_sb(t_line *line, int count)
{
	++count;
	ft_clear_line(line->len, line->left);
	(line->str)[0] = '\0';
	line->len = 0;
	line->left = 0;
	return ('i');
}
