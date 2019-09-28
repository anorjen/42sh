/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phash_init_builtins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 13:21:17 by sbearded          #+#    #+#             */
/*   Updated: 2019/06/27 14:03:56 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

extern t_hashtable	*g_hash_built;

static const char	*g_builtin_str[] = {
	"echo",
	"cd",
	"setenv",
	"unsetenv",
	"env",
	"exit",
	"alias",
	"unalias"
};

int					(*g_builtin_func[]) (char **) = {
	&ms_echo,
	&ms_cd,
	&ms_setenv,
	&ms_unsetenv,
	&ms_env,
	&ms_exit,
	&ms_alias,
	&ms_unalias
};

void		phash_init_builtins(void)
{
	int	i;

	i = -1;
	while (++i < NUM_BUILTINS)
		hash_insert(ft_strdup(g_builtin_str[i]), g_hash_built,
					g_builtin_func[i]);
}
