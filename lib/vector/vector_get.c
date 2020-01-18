/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcartwri <jcartwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 17:22:16 by jcartwri          #+#    #+#             */
/*   Updated: 2019/05/10 13:26:26 by jcartwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_lib.h"

TYPE	vector_get(t_vector_lib *vector, unsigned int num)
{
	if (vector == NULL || vector->arr == NULL)
		return (NULL);
	return (num >= vector->size) ? (NULL) : (vector->arr[num]);
}
