/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 16:22:26 by anorjen           #+#    #+#             */
/*   Updated: 2019/10/27 12:18:32 by sbearded         ###   ########.fr       */
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
