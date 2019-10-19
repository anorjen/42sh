/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 15:55:22 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/05 16:04:41 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# define COMMAND_PIPE 100
# define COMMAND_LREDIR 101
# define COMMAND_RREDIR 102
# define COMMAND_HEREDOC 103
# define COMMAND_APPEND 104
# define COMMAND_BACKGR 105
# define COMMAND_EXTERNAL 0

# include "stdlib.h"

t_job		*lexer(char **arg);
t_process	*new_segment(char **arg, int i);
void		input_path(char **arg, int i, t_process *new_process);
void		output_path(char **arg, int i, t_process *new_process);
void		*free_job(t_job *job);
void		new_agregation(char **arg, int i, t_process *new_process);
char		**new_query(char **arg, int i);
int			is_agrarg(char *line);
void		*free_process(t_process *proc);
void		*free_arg(char **arg);

#endif
