/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:52:35 by jcartwri          #+#    #+#             */
/*   Updated: 2019/06/22 10:18:22 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "alias.h"

static void ft_strdel_alias_mas(char **mas)
{
	int i;

	i = 0;
	while (mas[i])
	{
		ft_strdel(&mas[i]);
		i++;
	}
	free(mas);
}

int file_len(void)
{
	int		i;
	int		fd;
	char	*str;
	char 	**arr;

	i = 0;
	fd = open("~/.alias_profile", O_RDONLY);
	while (get_next_line(fd, &str) > 0)
	{
		arr = ft_strsplit(str, ' ');
		if (!arr || !arr[0] || !arr[1] || ft_strcmp(arr[0], "alias") != 0 || ft_strchr(arr[1], '=') == NULL)
			i--;
		ft_strdel_alias_mas(arr);
		ft_strdel(&str);
		i++;
	}
	close(fd);
	return (i);
}

int ft_add_alias(char *str, int i)
{
	char	**arr;
	char	**mas;

	arr = ft_strsplit(str, ' ');
	if (!arr || !arr[0] || !arr[1] || ft_strcmp(arr[0], "alias") != 0 || ft_strchr(arr[1], '=') == NULL)
	{
		ft_strdel_alias_mas(arr);
		return (-1);
	}
	g_alias[i] = arr[1];
	mas = ft_strsplit(arr[1], '=');
	vector_add(g_alias_key, mas[0]);
	vector_add(g_alias_value, mas[1]);
	free(arr);
	free(mas);
	return (0);
}

void alias_init(void)
{
	unsigned int	i;
	int 			len;
	int 			fd;
	char 			*str;

	i = 0;
	g_alias_value = vector_init();
	g_alias_key = vector_init();
	if (access("~/.zshrc", 0) == -1)
		return ;
	len = file_len();
	g_alias = (char **)malloc(sizeof(char *) * (len + 1));
	g_alias[len] = NULL;
	fd = open("~/.zshrc", O_RDONLY);
	while (get_next_line(fd, &str) > 0)
	{
		i += ft_add_alias(str, i);
		ft_strdel(&str);
		i++;
	}
	close(fd);
}
