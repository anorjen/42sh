/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 14:35:53 by anorjen           #+#    #+#             */
/*   Updated: 2019/11/16 18:55:37 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "history_search.h"

static void	run_editor(char **environ, t_fc fc)
{
	char	*str;
	char	**arg;
	char	*tmp;

	if (fc.e == 0)
		str = ft_strjoin("vi ", HISTORY_FILE);
	else
	{
		tmp = ft_strjoin(fc.editor, " ");
		str = ft_strjoin(tmp, HISTORY_FILE);
		free(tmp);
	}
	str = replace_dir(str, environ);
	arg = write_arg(str);
	free(str);
	kazekage(arg);
	if (g_h_session != NULL)
		free_hsess(g_h_session);
	init_search_history(ft_strlen(basename(g_sh->cur_dir))
												+ ft_strlen("⦿") + 1);
}

static int	check_query_str(char *str, t_fc *fc)
{
	int	j;

	if (str[0] == '-')
	{
		j = 0;
		while (str[++j] != '\0')
		{
			if (str[j] == 'l')
				fc->l = 1;
			else if (str[j] == 'n')
				fc->n = 1;
			else if (str[j] >= 48 && str[j] <= 57)
				fc->num = ft_atoi(&str[1]);
			else if (str[j] == 'e')
				fc->e = 1;
		}
	}
	else if (fc->e == 1 && fc->editor == NULL)
		fc->editor = str;
	else
		return (-1);
	return (0);
}

static int	check_query(char **query, t_fc *fc)
{
	int	i;
	int	st;

	i = 0;
	st = 0;
	while (query[++i] != NULL)
	{
		if ((st = check_query_str(query[i], fc)) != 0)
		{
			write(1, "fc: event not found\n", 21);
			return (-1);
		}
	}
	return (0);
}

static void	init_fc(t_fc *fc)
{
	fc->l = 0;
	fc->n = 0;
	fc->e = 0;
	fc->editor = NULL;
	fc->num = 0;
}

int			shell_fc(t_process *proc)
{
	int		qlen;
	char	**query;
	t_fc	fc;

	init_fc(&fc);
	query = proc->query;
	qlen = arrlen(query);
	if (check_query(query, &fc) == 0)
	{
		if (qlen == 1 || fc.e == 1)
			run_editor(g_sh->env, fc);
		else
		{
			if (fc.l == 1)
				print_history(g_h_session, fc.num, fc.n);
		}
	}
	return (1);
}
