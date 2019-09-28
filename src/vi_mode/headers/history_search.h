/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 14:00:12 by anorjen           #+#    #+#             */
/*   Updated: 2019/09/28 15:32:17 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_SEARCH_H
# define HISTORY_SEARCH_H

# include "libft.h"
# include "vi_input.h"
# include "ft_dlist.h"


/*
**	hi_search_history
*/
void	ft_history_search(char *line);
char	*ft_history_last();
char	*ft_history_word(char *word);
char	*ft_history_number(int number);

#endif