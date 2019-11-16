/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:28:13 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:28:15 by mgorczan         ###   ########.fr       */
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
