/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_del_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcartwri <jcartwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 16:07:55 by jcartwri          #+#    #+#             */
/*   Updated: 2019/05/10 13:26:26 by jcartwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_lib.h"

int		vector_del_value(t_vector_lib *vector, TYPE elem, unsigned int begin,
		unsigned int end)
{
	long index;

	if ((index = vector_search(vector, elem, begin, end)) == -1)
		return (0);
	return (vector_del(vector, index));
}
