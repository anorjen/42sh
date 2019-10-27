/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 16:22:26 by anorjen           #+#    #+#             */
/*   Updated: 2019/05/31 17:23:37 by anorjen          ###   ########.fr       */
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