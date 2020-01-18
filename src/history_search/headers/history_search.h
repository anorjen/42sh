/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 14:08:35 by anorjen           #+#    #+#             */
/*   Updated: 2019/11/30 20:44:15 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_SEARCH_H
# define HISTORY_SEARCH_H

# include "libft.h"
# include "input.h"

typedef struct		s_fc
{
	int				e;
	char			*editor;
	int				l;
	int				n;
	int				r;
	int				num;
}					t_fc;

/*
**	hi_search_history
*/
char				*g_search_word;
t_history_session	*g_old_search;
t_history_session	*search_all_str(t_history_session *h_session);
t_history_session	*search_last(t_history_session *h_session);
t_history_session	*search_word(t_history_session *h_session, char *word);
t_history_session	*search_number(t_history_session *h_session, int number);

t_history_session	*list_rewind_to_begin(t_history_session *h_session);
t_history_session	*list_rewind_to_end(t_history_session *h_session);
int					listlen(t_history_session *dlst);
int					arrlen(char **query);

void				print_history(t_history_session *h_session, t_fc *fc);
void				key_search(t_history_session *h_session);

int					save_history();

#endif
