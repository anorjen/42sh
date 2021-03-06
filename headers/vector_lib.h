/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_lib.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:46:37 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:46:38 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _VECTOR_LIB_H
# define _VECTOR_LIB_H

# include <stdlib.h>

# define STACK_STEP 100
# if STACK_STEP < 1
#  error STACK_STEP must be >= 1
# endif
# define TYPE void*

typedef struct		s_vector_lib
{
	TYPE			*arr;
	unsigned int	size;
}					t_vector_lib;

t_vector_lib		*vector_init(void);
int					vector_resize(t_vector_lib *vector, unsigned int new_size);
int					vector_add(t_vector_lib *vector, TYPE elem);
int					vector_del(t_vector_lib *vector, unsigned int num);
int					vector_del_value(t_vector_lib *vector, TYPE elem,
		unsigned int begin, unsigned int end);
TYPE				vector_get(t_vector_lib *vector, unsigned int num);
int					vector_set(t_vector_lib *vector, unsigned int num,
																TYPE elem);
long				vector_search(t_vector_lib *vector, TYPE elem,
		unsigned int begin, unsigned int end);
void				vector_deinit(t_vector_lib **vector);

#endif
