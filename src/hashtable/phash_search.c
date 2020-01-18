/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phash_search.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:44:34 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 21:44:34 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

void		*phash_search(const char *str, int status)
{
	t_buck_cont	*item;

	item = NULL;
	if (status == HASH_FILES)
		item = hash_search(str, g_hash_files);
	else if (status == HASH_DIRS)
		item = hash_search(str, g_hash_dirs);
	else if (status == HASH_BUILT)
		item = hash_search(str, g_hash_built);
	else if (status == HASH_PARAM_EXP)
		item = hash_search(str, g_hash_param_exp);
	if (item)
		return (item->data);
	else
		return (NULL);
}
