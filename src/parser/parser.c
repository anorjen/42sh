/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 16:53:05 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/25 21:52:41 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void					replace_str(char **chang_line, int i, int lenght, char *env_verb)
{
	char *temp;
	char *tmp;

	temp = *chang_line;
	*chang_line = ft_strsub(temp, 0, i);
	tmp = *chang_line;
	*chang_line = ft_strjoin(tmp, env_verb);
	free(tmp);
	tmp = *chang_line;
	*chang_line = ft_strjoin(tmp, &temp[lenght]);
	free(tmp);
	free(temp);
	
}

void					check_quote(t_control_multiply_line *control, char ch)
{

	if ((ch == '\"' || ch == '\'') && (control->quote % 2) == 0)
	{
		control->ch_quote = ch;
		control->quote++;
	}
	else if (ch == control->ch_quote)
	{
		control->quote--;
	}
}

t_control_multiply_line	init_control(void)
{
	t_control_multiply_line control;

	control.quote = 0;
	control.ch_quote ='\0';
	control.pipe = 0;
	control.els = 0;
	control.ch = 0;
	return (control);
}




char					**parser(t_history_session **h_session, char **env, int lenght_hello)
{
	char	**arg;
	char	*line;
	int		mode;
	int		count_arg;


//--------------------------------
//	if ((termcap = get_termcap(env)))
//		set_termenv(termcap);
//	set_keypress();
//	*h_session = add_history(*h_session, lenght_hello);
//	mode = 0;
//	while (1)
//	{
//		line = input(h_session, lenght_hello, mode);
//		mode = multiply_line(line);
//		if (mode == -1)
//		{
//			reset_keypress();
//			free(term);
//			free(line);
//			return (NULL);
//		}
//		if (!mode)
//			break ;
//		free(line);
//	}
	//--------------------------------



	line = read_ln();

	line = replace_env(line, env);
	line = replace_dir(line, env);
	arg = write_arg(line);
//	int i = 0;
//	while (arg && arg[i])
//		ft_printf("%s\n", arg[i++]);
//	ft_printf("\n\n");
	free(line);



	return (arg);
}

