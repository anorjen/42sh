/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:30:34 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 21:30:36 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

# include "libft.h"

# define BUFF 32

char	*str_new();
char	*str_addback(char **dest, char *src, int num);
char	*str_substr(char *str, int start, int len);
char	*str_union(char **dest, char *src, int pos);

#endif
