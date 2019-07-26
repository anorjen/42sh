/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 16:53:47 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/25 15:25:23 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H 

// # define COMMANDID_QUOTE 1

# define COMMAND_QUOTE "dquote> "
// # define COMMAND_END "cmdand> "
// # define COMMAND_ELSE "cmdor> "
// # define COMMAND_PIPE "pipe> "
// # define COMMAND_NEW_LINE "> "
// # define COMMAND_ERROR "21sh: parse error near "

# define TOKEN_BACKGRAUND 1
# define TOKEN_AND 2
# define TOKEN_OR 2
# define TOKEN_PIPE 1
# define TOKEN_INPUTPATH 1
# define TOKEN_HEREDOK 2
# define TOKEN_OUTPUTPATH 1
# define TOKEN_AGRAGATION 2
# define TOKEN_UPPEND 2

# define MODE_HEREDOC 100
# define MODE_QUOTE 101
# define MODE_PIPE 102
# define MODE_OR 103
# define MODE_BACKGROUND 104
# define MODE_AND 105
# define MODE_MULTILINE 106


#include "input.h"


char    **parser(t_history_session **h_session, char **env, int lenght_hello);
char    *replace_env(char *line, char **env);
void	replace_str(char **chang_line, int i, int lenght, char *env_verb);
int		is_delimetr(char ch);
char    *replace_dir(char *line, char **env);
int		spec_token(char *line, int j);
int		is_agregation(char *line, int j);
char	*get_token(char *line, int *j);


char    **write_arg(char *line);
int	parse_error(char *line);
int						multiply_line(char *line);
int is_redir(char *line, int i);
int is_specdel(char *line, int i);



#endif