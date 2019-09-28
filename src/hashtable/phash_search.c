/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phash_search.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:13:16 by sbearded          #+#    #+#             */
/*   Updated: 2019/09/28 16:58:13 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/hashtable.h"

extern t_hashtable	*g_hash_files;
extern t_hashtable	*g_hash_dirs;
extern t_hashtable	*g_hash_built;

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
	if (item)
		return (item->data);
	else
		return (NULL);
}
