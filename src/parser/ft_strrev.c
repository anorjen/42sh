/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 17:03:47 by sbearded          #+#    #+#             */
/*   Updated: 2019/12/03 17:27:04 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strrev(char *str)
{
	char	*rev;
	size_t	len;
	size_t	i;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	rev = ft_strnew(len);
	i = 0;
	while (i < len)
	{
		rev[i] = str[len - i - 1];
		i++;
	}
	return (rev);
}

int		is_redir(char *line, int i)
{
	if (!line)
		return (0);
	if (line[i] == '>' && line[i + 1] == '>')
		return (2);
	else if (line[i] == '>')
		return (1);
	else if (line[i] == '<' && line[i + 1] == '<')
		return (2);
	else if (line[i] == '<')
		return (1);
	return (0);
}
