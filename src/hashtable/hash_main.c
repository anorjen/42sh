/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 14:14:51 by sbearded          #+#    #+#             */
/*   Updated: 2019/06/20 14:38:01 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

t_hashtable		*hash_create(int buckets)
{
	t_hashtable	*new_table;
	int			i;

	new_table = (t_hashtable *)gc_malloc(sizeof(t_hashtable));
	if (buckets == 0)
		buckets = DEFAULT_HASH_BUCKETS;
	new_table->bucket_array = (t_buck_cont **)gc_malloc(
									buckets * sizeof(t_buck_cont*));
	new_table->nbuckets = buckets;
	new_table->nentries = 0;
	i = 0;
	while (i < buckets)
	{
		new_table->bucket_array[i] = (t_buck_cont*)NULL;
		i++;
	}
	return (new_table);
}

unsigned int	hash_string(const char *s)
{
	unsigned int	i;

	i = FNV_OFFSET;
	while (*s)
	{
		i *= FNV_PRIME;
		i ^= *s;
		s++;
	}
	return (i);
}

int				hash_bucket(const char *str,
							t_hashtable *table,
							unsigned int *h)
{
	int	flag;
	int	res;

	if (table == NULL || str == NULL)
		return (0);
	flag = 0;
	if (h == NULL)
	{
		if ((h = (unsigned int *)malloc(sizeof(unsigned int))) == NULL)
			return (0);
		flag = 1;
	}
	*h = hash_string(str);
	res = *h & (table->nbuckets - 1);
	if (flag == 1)
		free(h);
	return (res);
}
