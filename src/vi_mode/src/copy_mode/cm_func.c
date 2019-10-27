/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cm_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:12:38 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:12:41 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

char		*ft_copy(char *line, int start_pos, int end_pos)
{
	int		len;
	char	*str;

	len = end_pos - start_pos;
	str = str_substr(line, start_pos, len);
	return (str);
}

void		ft_paste(char **line, int *len, int *left, char *buf)
{
	int	pos;
	int	i;

	if (buf)
	{
		pos = *len - *left;
		*line = str_union(line, buf, pos);
		ft_clear_line(*len, *left);
		*len += ft_strlen(buf);
		write(1, *line, *len);
		i = 0;
		while (i < *left)
			arrow_left(*len, &i);
	}
}

char		*ft_cut(char **line, int start_pos, int *len, int *left)
{
	char	*str;
	int		size;
	int		i;

	size = *len - *left - start_pos;
	str = str_substr(*line, start_pos, size);
	ft_memcpy(&(*line)[start_pos], &(*line)[*len - *left], *left);
	i = start_pos + *left - 1;
	while (++i < *len)
		(*line)[i] = '\0';
	ft_clear_line(*len, *left);
	*len = start_pos + *left;
	write(1, *line, *len);
	i = 0;
	while (i < *left)
		arrow_left(*len, &i);
	return (str);
}
