/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 14:08:35 by anorjen           #+#    #+#             */
/*   Updated: 2019/11/16 15:09:11 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_SEARCH_H
# define HISTORY_SEARCH_H
# define HISTORY_FILE "~/.42sh_history"
# include "libft.h"
# include "input.h"

/*
**	hi_search_history
*/

void				search_all_str(t_history_session *h_session, char *line);
void				search_last(t_history_session *h_session);
void				search_word(t_history_session *h_session, char *word);
void				search_number(t_history_session *h_session, int number);

t_history_session	*list_rewind_to_begin(t_history_session *h_session);
t_history_session	*list_rewind_to_end(t_history_session *h_session);
int					listlen(t_history_session *dlst);
int					arrlen(char **query);

void				print_history(t_history_session *h_session, int num, int n);
void				key_search(t_history_session *h_session);

int					save_history();

#endif
