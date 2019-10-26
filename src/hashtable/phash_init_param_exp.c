/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phash_init_param_exp.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 11:20:03 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/26 11:48:57 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

const char	*g_param_exp_str[] = {
	":",
	":-",
	":+",
	":=",
	":?",
	"%",
	"%%",
	"#",
	"##",
	NULL
};

char		*(*g_param_exp_func[]) (t_exp *) = {
	&param_exp_colon,
	&param_exp_minus,
	&param_exp_plus,
	&param_exp_equal,
	&param_exp_question,
	&param_exp_percent,
	&param_exp_percent_d,
	&param_exp_hash,
	&param_exp_hash_d,
	NULL
};

void		phash_init_param_exp(void)
{
	int	i;

	i = -1;
	while (++i < NUM_PARAM_EXP)
		hash_insert(ft_strdup(g_param_exp_str[i]), g_hash_param_exp,
					g_param_exp_func[i]);
}
