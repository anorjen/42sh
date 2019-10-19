/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 14:14:55 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/19 13:16:53 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

# include "minishell.h"

#include <dirent.h>

# define DEFAULT_HASH_BUCKETS 128

# define FNV_OFFSET 2166136261
# define FNV_PRIME 16777619

# define HASH_NUM 3

# define HASH_DIRS 0
# define HASH_BUILT 1
# define HASH_FILES 2

# define NUM_BUILTINS ((int)(sizeof(g_builtin_str) / sizeof(char *)))

# define ISTYPE(mode, mask)	(((mode) & S_IFMT) == (mask))
# define ISREG(mode)		ISTYPE((mode), S_IFREG)
# define ISDIR(mode)		ISTYPE((mode), S_IFDIR)

typedef struct					s_buck_cont
{
	struct s_buck_cont			*next;
	char						*key;
	void						*data;
	unsigned int				k_hash;
}								t_buck_cont;

typedef struct					s_hashtable
{
	t_buck_cont					**bucket_array;
	int							nbuckets;
	int							nentries;
}								t_hashtable;

t_hashtable						*g_hash_built;
t_hashtable						*g_hash_dirs;
t_hashtable						*g_hash_files;

t_hashtable						*hash_create(	int buckets);
unsigned int					hash_string(	const char *s);

int								hash_bucket(	const char *str,
												t_hashtable *table,
												unsigned int *h);

t_buck_cont						*hash_search(	const char *str,
												t_hashtable *table);

t_buck_cont						*hash_remove(	const char *str,
												t_hashtable *table);

t_buck_cont						*hash_insert(	const char *str,
												t_hashtable *table,
												void *data);

void							hash_free_item(	t_buck_cont *item,
												const char *str,
												t_hashtable *table,
												void (*free_f)(void *));

void							hash_clean_table(t_hashtable *table,
												void (*free_f)(void *));

void							hash_free_table(t_hashtable *table);

void							hash_delete_table(t_hashtable *table,
												void (*free_f)(void *));

void							phash_init(void);
void							phash_init_builtins(void);
void							phash_deinit(void);
void							*phash_search(const char *str, int status);
void							phash_update(void);

char							*ft_get_path(char *path, char *name);

#endif
