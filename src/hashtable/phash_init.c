/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phash_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:44:22 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:44:23 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

void		phash_init(void)
{
	g_hash_files = hash_create(0);
	g_hash_dirs = hash_create(0);
	g_hash_built = hash_create(20);
	g_hash_param_exp = hash_create(20);
	phash_init_builtins();
	phash_init_param_exp();
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
