/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 14:35:53 by anorjen           #+#    #+#             */
/*   Updated: 2019/10/26 17:30:51 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "history_search.h"

typedef struct	s_fc
{
	int			l;
	int			n;
	int			num;
}				t_fc;

static void	run_vi(char **environ)
{
	char	*str;
	char	**arg;

	str = ft_strjoin("vi ", "~/.42sh_history");
	str = replace_dir(str, environ);
	arg = write_arg(str);
	free(str);
	kazekage(arg);
	// init_history();
}

static int	check_query_str(char *str, t_fc *fc)
{
	int	j;

	if (str[0] == '-')
	{
		j = 0;
		while (str[++j] != '\0')
		{
			if (str[j] == 'l' || str[j] == 'n'
				|| (str[j] >= 48 && str[j] <= 57))
			{
				if (str[j] == 'l')
					fc->l = 1;
				else if (str[j] == 'n')
					fc->n = 1;
				else if (str[j] >= 48 && str[j] <= 57)
					fc->num = ft_atoi(&str[1]);
			}
			else
				return (-1);
		}
	}
	return (0);
}

static int	check_query(char **query, t_fc *fc)
{
	int	i;
	int	st;

	i = 0;
	st = 0;
	while(query[++i] != NULL)
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
	fc->num = 0;
}

int			shell_fc(t_process *proc)
{
	extern char	**environ;
	int			qlen;
	char		**query;
	t_fc		fc;

	init_fc(&fc);
	query = proc->query;
	qlen = arrlen(query);
	if (qlen == 1)
		run_vi(environ);
	else
	{
		if (check_query(query, &fc) == 0)
		{
			if (fc.l == 1)
				print_history(g_h_session, fc.num, fc.n);
		}
	}
	return (1);
}
