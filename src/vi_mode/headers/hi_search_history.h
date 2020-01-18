/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hi_search_history.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:30:05 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 21:30:07 by sbearded         ###   ########.fr       */
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
