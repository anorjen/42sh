/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 22:40:26 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/25 22:40:26 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void					stdin_heredoc(t_process *proc, h_launch *launch, char *line)
{
	FILE				*fp;

	fp = fopen ("/tmp/stdin","w");
	fprintf (fp,"%s\n", line);
	fclose (fp);
	if (proc->input_path == NULL)
		proc->input_path = "/tmp/stdin";
}

char					*str_join_her(char *s1, char *s2)
{
	char				*temp;

	if (!s1)
	{
		if (s2)
			s1 = ft_strdup(s2);
		else
			return (ft_strdup("\n"));
	}
	else
	{
		if (s2)
		{
			temp = s1;
			s1 = ft_strjoin(s1, "\n");
			free(temp);
			temp = s1;
			s1 = ft_strjoin(s1, s2);
			free(temp);
		}
		else
		{
			temp = s1;
			s1 = ft_strjoin(s1, "\n");
			free(temp);
		}
	}
	return (s1);
}

char					*readline_her(t_process *proc, int i)
{
	char				*line;
	char				*temp;
	t_history_session	*h_session;

	line = NULL;
	temp = NULL;
	h_session = NULL;
	while(21)
	{
		h_session = add_history(h_session, ft_strlen("heredoc> "));
		temp = input(&h_session, ft_strlen("heredoc> "), MODE_HEREDOC, shell->env);
		free_hsess(h_session);
		h_session = NULL;
		if (temp && !ft_strcmp(temp, proc->heredoc[i]))
			break ;
		line = str_join_her(line, temp);
		if (temp)
			free(temp);
	}
	return (line);
}


void					launch_heredoc(t_process *proc, h_launch *launch)
{
	int					i;
	char				*line;

	i = 0;
	line = NULL;
	while (proc->heredoc && proc->heredoc[i])
	{
		if (line)
			free(line);
		line = readline_her(proc, i);
		++i;
	}
	stdin_heredoc(proc, launch, line);
}
