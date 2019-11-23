/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:18:00 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:18:02 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

static int	count_words(char *str)
{
	int	i;
	int	num;

	num = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ' && (str[i + 1] == ' ' || str[i + 1] == '\0'))
			++num;
	}
	return (num);
}

static char	*ft_swapw(char *str)
{
	int		i;
	int		j;
	char	*newstr;

	j = 0;
	if (count_words(str) == 2 && (newstr = ft_strnew(ft_strlen(str))))
	{
		i = -1;
		while (str[++i])
			if (str[i] == ' ' && str[i + 1] != ' ')
				break ;
		while (str[++i])
			newstr[j++] = str[i];
		i = -1;
		while (str[++i])
			if (str[i] != ' ' && str[i + 1] == ' ')
				break ;
		while (str[++i] == ' ')
			newstr[j++] = str[i];
		i = -1;
		while (str[++i] != ' ')
			newstr[j++] = str[i];
		return (newstr);
	}
	return (NULL);
}

static int	get_start(char *str, int pos)
{
	int	i;

	i = -1;
	while (++i < 2)
	{
		while (pos >= 0)
		{
			if ((pos == 0 || str[pos - 1] == ' ') && str[pos] != ' ')
				break ;
			--pos;
		}
		--pos;
	}
	return (pos + 1);
}

static int	get_end(char *str, int pos, int len)
{
	while (pos < len)
	{
		if ((str[pos + 1] == '\0' || str[pos + 1] == ' ') && str[pos] != ' ')
			break ;
		++pos;
	}
	return (pos);
}

void		ft_swap_words(t_line *line)
{
	int		pos;
	char	*words[2];
	int		start;
	int		len;

	pos = line->len - line->left;
	if (pos > 0)
	{
		start = get_start(line->str, pos);
		len = get_end(line->str, pos, line->len) - start + 1;
		if (start >= 0 && len + start - 1 < line->len
			&& (words[0] = str_substr(line->str, start, len)))
		{
			if ((words[1] = ft_swapw(words[0])) != NULL)
			{
				vi_h(line, pos - start);
				write(1, words[1], ft_strlen(words[1]));
				ft_memmove(&(line->str)[start], words[1], len);
				line->left -= len;
				free(words[1]);
			}
			free(words[0]);
		}
	}
}
