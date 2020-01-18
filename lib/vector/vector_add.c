/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcartwri <jcartwri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:46:08 by jcartwri          #+#    #+#             */
/*   Updated: 2019/04/30 15:51:24 by jcartwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_lib.h"

int		vector_add(t_vector_lib *vector, TYPE elem)
{
	if (vector == NULL || vector->arr == NULL)
		return (0);
	(vector)->arr[vector->size++] = elem;
	if ((vector->size % STACK_STEP) == 0)
		return (vector_resize(vector, vector->size + STACK_STEP));
	return (1);
}
