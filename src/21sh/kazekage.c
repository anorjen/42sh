/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kazekage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 22:00:55 by sbearded          #+#    #+#             */
/*   Updated: 2020/01/18 19:35:27 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_glodel(char *line)
{
	if (!ft_strcmp(line, ";"))
		return (1);
	else if (!ft_strcmp(line, "&"))
		return (1);
	else if (!ft_strcmp(line, "&&"))
		return (2);
	else if (!ft_strcmp(line, "||"))
		return (2);
	return (0);
}

char	**new_sg(char **arg, int i, int lenght)
{
	char	**new_arg;
	int		j;
	int		temp;

	j = 0;
	if ((lenght - i + 1) == 0)
		return (NULL);
	if ((new_arg = (char**)malloc(sizeof(char*) * (lenght - i + 1))) == NULL)
		exit(1);
	temp = i;
	while (j < (lenght - temp))
	{
		new_arg[j] = ft_strdup(arg[i]);
		i++;
		j++;
	}
	new_arg[j] = NULL;
	return (new_arg);
}

char	**split_segment(char **arg)
{
	char	**new_arg;
	int		i;

	i = 0;
	while (arg[i] && !is_glodel(arg[i]))
		++i;
	if (arg[i] && !ft_strcmp(arg[i], "&"))
		++i;
	new_arg = new_sg(arg, 0, i);
	return (new_arg);
}

char	**segment_off(char **arg, int *mode)
{
	int		i;
	int		lenght;
	char	**new_arg;

	i = 0;
	while (arg[i] && !is_glodel(arg[i]))
		++i;
	if (!arg[i])
	{
		free_arg(arg);
		return (NULL);
	}
	!ft_strcmp(arg[i], ";") ? *mode = 1 : 0;
	!ft_strcmp(arg[i], "&") ? *mode = 2 : 0;
	!ft_strcmp(arg[i], "&&") ? *mode = 3 : 0;
	!ft_strcmp(arg[i], "||") ? *mode = 4 : 0;
	lenght = ++i;
	while (arg[lenght])
		++lenght;
	new_arg = new_sg(arg, i, lenght);
	i = 0;
	while (arg[i])
		free(arg[i++]);
	free(arg);
	return (new_arg);
}

void	kazekage(char **arg)
{
	t_job	*job;
	char	**segment_arg;
	int		mode;
	int		status;
	int		prev_mode;

	status = 0;
	mode = 0;
	while (arg)
	{
		segment_arg = split_segment(arg);
		segment_arg = replace_env_wrapper(segment_arg);
		segment_arg = replace_alias(segment_arg);
		prev_mode = mode;
		arg = segment_off(arg, &mode);
		job = lexer(segment_arg);
		free_arg(segment_arg);
		if ((prev_mode == 3 && status) || (prev_mode == 4 && !status))
			continue ;
		if (job && job->root)
			status = shell_launch_job(job);
		if (mode == 2 && !status)
			break ;
	}
}
