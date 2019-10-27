/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_w.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:29:07 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:29:08 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

int	vi_w(t_line *line, int count)
{
	while (count-- && line->left > 0)
		ft_key_next(line->str, line->len, &(line->left));
	return (0);
}
