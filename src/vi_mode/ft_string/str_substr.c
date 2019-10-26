/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_substr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:13:13 by anorjen           #+#    #+#             */
/*   Updated: 2019/05/22 19:49:41 by anorjen          ###   ########.fr       */
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
