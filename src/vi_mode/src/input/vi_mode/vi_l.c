/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_l.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:27:44 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:27:45 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

int	vi_l(t_line *line, int count)
{
	count = (count > line->left ? line->left : count);
	while (count--)
		arrow_right(&(line->left));
	return (0);
}
