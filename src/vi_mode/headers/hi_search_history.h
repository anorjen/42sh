/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hi_search_history.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 14:04:25 by anorjen           #+#    #+#             */
/*   Updated: 2019/10/27 12:18:54 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HI_SEARCH_HISTORY_H
# define HI_SEARCH_HISTORY_H

# include "libft.h"
# include "vi_input.h"
# include "ft_dlist.h"

/*
**	hi_search_history
*/
void	ft_history_search(char *line);
char	*ft_history_last(void);
char	*ft_history_word(char *word);
char	*ft_history_number(int number);

#endif
