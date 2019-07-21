/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 16:53:47 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/18 16:53:48 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H 

# define COMMANDID_QUOTE 1

# define COMMAND_QUOTE "dquote> "
# define COMMAND_END "cmdand> "
# define COMMAND_ELSE "cmdor> "
# define COMMAND_PIPE "pipe> "
# define COMMAND_NEW_LINE "> "
# define COMMAND_ERROR "21sh: parse error near "

# define TOKEN_BACKGRAUND 1
# define TOKEN_AND 2
# define TOKEN_OR 2
# define TOKEN_PIPE 1
# define TOKEN_INPUTPATH 1
# define TOKEN_HEREDOK 2
# define TOKEN_OUTPUTPATH 1
# define TOKEN_AGRAGATION 2
# define TOKEN_UPPEND 2







#include "input.h"

typedef struct  s_control_multiply_line
{
    int     quote;
    char    ch_quote;
    int     pipe;
    int     and;
    int     els;
    int     ch;
}               t_control_multiply_line;

char    **parser(t_history_session **h_session, char **env, int lenght_hello);
char    *replace_env(char *line, char **env);
void	replace_str(char **chang_line, int i, int lenght, char *env_verb);
int			is_delimetr(char ch);
char    *replace_dir(char *line, char **env);
int		spec_token(char *line, int j);

char    **write_arg(char *line);



#endif