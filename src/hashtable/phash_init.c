/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phash_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 17:28:38 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/05 15:45:48 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/hashtable.h"

void		phash_init(void)
{
	g_hash_files = hash_create(0);
	g_hash_dirs = hash_create(0);
	g_hash_built = hash_create(20);
	phash_init_builtins();
	phash_update();
}

void		non_free_data(void *data)
{
	data = NULL;
}

void		phash_deinit(void)
{
	hash_delete_table(g_hash_files, NULL);
	hash_delete_table(g_hash_dirs, NULL);
	hash_delete_table(g_hash_built, non_free_data);
}
