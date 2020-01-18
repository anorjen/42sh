/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:31:38 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 21:31:40 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

# include "minishell.h"

# include <dirent.h>

# define DEFAULT_HASH_BUCKETS 128

# define FNV_OFFSET 2166136261
# define FNV_PRIME 16777619

# define HASH_NUM 3

# define HASH_DIRS 0
# define HASH_BUILT 1
# define HASH_FILES 2
# define HASH_PARAM_EXP 3

# define NUM_BUILTINS ((int)(sizeof(g_builtin_str) / sizeof(char *))) - 1
# define NUM_PARAM_EXP ((int)(sizeof(g_param_exp_str) / sizeof(char *))) - 1

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
t_hashtable						*g_hash_param_exp;

t_hashtable						*hash_create(int buckets);
unsigned int					hash_string(const char *s);

int								hash_bucket(const char *str,
												t_hashtable *table,
												unsigned int *h);

t_buck_cont						*hash_search(const char *str,
												t_hashtable *table);

t_buck_cont						*hash_remove(const char *str,
												t_hashtable *table);

t_buck_cont						*hash_insert(const char *str,
												t_hashtable *table,
												void *data);

void							hash_free_item(t_buck_cont *item,
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
void							phash_init_param_exp(void);
void							phash_deinit(void);
void							*phash_search(const char *str, int status);
void							phash_update(void);

char							*ft_get_path(char *path, char *name);

#endif
