/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_v.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:28:27 by anorjen           #+#    #+#             */
/*   Updated: 2019/10/26 17:32:33 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

#define TMP_FILE "42sh.tmp"

static char	*readstr()
{
	int		fd;
	char	*str;
	char	buf[101];
	char	*tmp;
	int		ret;

	str = NULL;
	if ((fd = open(TMP_FILE, O_RDONLY)) != -1)
	{
		while (1)
		{
			ret = read(fd, &buf, 100);
			buf[ret] = '\0';
			if (ret == 0 || ret == -1)
				break ;
			tmp = str;
			str = ft_strjoin(str, buf);
			if (tmp != NULL)
				free(tmp);
		}
		close(fd);
		remove(TMP_FILE);
	}
	return str;
}

static int	writestr(t_line *line)
{
	int	fd;

	if ((fd = open(TMP_FILE, O_WRONLY | O_CREAT,
			S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH)) != -1)
	{
		write(fd, line->str, line->len);
		close(fd);
		return (1);
	}
	return (0);
}

int		vi_v(t_line *line, int count)
{
	char	**arg;
	char	*str;

	++count;
	if (writestr(line))
	{
		str = ft_strjoin("vi ", TMP_FILE);
		arg = write_arg(str);
		free(str);
		kazekage(arg);
		if ((str = readstr()) != NULL)
		{
			ft_clear_line(line->len, line->left);
			line->str = str;
			line->len = ft_strlen(str);
			line->left = 0;
			write(1, line->str, line->len);
		}
		return (KC_NL);
	}
	return (0);
}
