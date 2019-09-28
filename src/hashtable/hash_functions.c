/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 14:21:05 by sbearded          #+#    #+#             */
/*   Updated: 2019/06/20 18:54:56 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

t_buck_cont		*hash_search(const char *str, t_hashtable *table)
{
	t_buck_cont		*lst;
	int				bucket;
	unsigned int	hv;

	if (table == NULL || str == NULL || table->bucket_array == NULL)
		return (NULL);
	bucket = hash_bucket(str, table, &hv);
	lst = table->bucket_array[bucket];
	while (lst)
	{
		if (hv == lst->k_hash && ft_strcmp(lst->key, str) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

t_buck_cont		*hash_remove(const char *str, t_hashtable *table)
{
	t_buck_cont		*lst;
	t_buck_cont		*prev;
	int				bucket;
	unsigned int	hv;

	if (table == NULL || str == NULL || table->bucket_array == NULL)
		return (NULL);
	bucket = hash_bucket(str, table, &hv);
	lst = table->bucket_array[bucket];
	prev = NULL;
	while (lst)
	{
		if (hv == lst->k_hash && ft_strcmp(lst->key, str) == 0)
		{
			if (prev)
				prev->next = lst->next;
			else
				table->bucket_array[bucket] = lst->next;
			table->nentries--;
			return (lst);
		}
		prev = lst;
		lst = lst->next;
	}
	return (NULL);
}

t_buck_cont		*hash_insert(const char *str, t_hashtable *table, void *data)
{
	t_buck_cont		*item;
	int				bucket;
	unsigned int	hv;

	if (str == NULL)
		return (NULL);
	if (table == NULL)
		table = hash_create(0);
	if ((item = hash_search(str, table)))
	{
		free((void*)str);
		free(data);
	}
	else if (item == NULL)
	{
		bucket = hash_bucket(str, table, &hv);
		item = (t_buck_cont*)malloc(sizeof(t_buck_cont));
		item->next = table->bucket_array[bucket];
		table->bucket_array[bucket] = item;
		item->data = data;
		item->key = (char*)str;
		item->k_hash = hv;
		table->nentries++;
	}
	return (item);
}
