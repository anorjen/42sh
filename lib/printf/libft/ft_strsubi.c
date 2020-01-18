/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsubi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 08:41:28 by sbearded          #+#    #+#             */
/*   Updated: 2018/12/05 16:55:45 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsubi(char const *s, unsigned int start, unsigned int end)
{
	char	*new_arr;
	char	*fresh;

	fresh = (char *)malloc((end - start) + 2);
	if (fresh == NULL)
		return (NULL);
	new_arr = fresh;
	while (s[start] != '\0' && start <= end)
		*(fresh++) = s[start++];
	*fresh = '\0';
	return (new_arr);
}
