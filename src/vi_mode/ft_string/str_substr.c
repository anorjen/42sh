/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_substr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:50:06 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 21:50:08 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*str_substr(char *str, int start, int len)
{
	char	*substr;
	int		size;

	if (start < 0 || len <= 0 || str == NULL)
		return (NULL);
	size = (len / BUFF + 1) * BUFF;
	substr = ft_strnew(size);
	if (substr)
		ft_memcpy(substr, &(str[start]), len);
	return (substr);
}
