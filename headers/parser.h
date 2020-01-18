/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:46:58 by sbearded          #+#    #+#             */
/*   Updated: 2019/10/27 21:46:59 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# define COMMANDID_QUOTE 1
# define COMMAND_QUOTE "dquote> "
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
# include "input.h"
# include "alias.h"

char	**parser(t_history_session **h_session, char **env, int lenght_hello);
char	*check_env_verb(char *line, int i, int *lenght);
char	*replace_env(char *line, char **env);
char	*replace_param(char *line, int i, int *length);
void	replace_str(char **chang_line, int i, int lenght, char *env_verb);
int		is_delimetr(char ch);
char	*replace_dir(char *line, char **env);
int		spec_token(char *line, int j);
int		is_agregation(char *line, int j);
char	*get_token(char *line, int *j);
char	**write_arg(char *line);
int		multiply_line(t_history_session *h_session, char *line);
int		is_specdel(char *line, int i);
int		is_redir(char *line, int i);
int		parse_error(char *line);
char	**replace_alias(char **argv);
char	**replace_env_wrapper(char **argv);

#endif
