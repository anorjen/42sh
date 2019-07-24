/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 15:55:22 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/23 15:55:23 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#define COMMAND_EXTERNAL 0
#define COMMAND_EXIT 1
#define COMMAND_CD 2
#define COMMAND_JOBS 3
#define COMMAND_FG 4
#define COMMAND_BG 5
#define COMMAND_KILL 6
#define COMMAND_EXPORT 7
#define COMMAND_UNSET 8
#define COMMAND_HELP 9

# define COMMAND_PIPE 100
# define COMMAND_LREDIR 101
# define COMMAND_RREDIR 102
# define COMMAND_HEREDOC 103
# define COMMAND_APPEND 104



// # define IS_PIPE "|"
// # define IS_LREDIR "<"
// # define IS_RREDIR ">"
// # define IS_HEREDOC "<<"
// # define IS_APPEND ">>"
// agregation




#include "stdlib.h"




t_job	*lexer(char **arg);

t_process	*new_segment(char **arg, int i);

void    input_path(char **arg, int i, t_process *new_process); 
void    output_path(char **arg, int i, t_process *new_process);
void    free_job(t_job *job);




#endif
