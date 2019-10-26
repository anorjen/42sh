/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_ft_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD:src/vi_mode/src/input/in_ft_put.c
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 15:11:39 by anorjen           #+#    #+#             */
/*   Updated: 2019/10/26 17:03:06 by sbearded         ###   ########.fr       */
=======
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 15:11:39 by anorjen           #+#    #+#             */
/*   Updated: 2019/09/28 15:34:07 by anorjen          ###   ########.fr       */
>>>>>>> anorjen:src/vi_mode/src/input/in_ft_put.c
/*                                                                            */
/* ************************************************************************** */

#include "vi_input.h"

int	ft_put(int c)
{
	write(1, &c, 1);
	return (0);
}
