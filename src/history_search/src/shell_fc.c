/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 14:35:53 by anorjen           #+#    #+#             */
/*   Updated: 2019/10/26 17:14:18 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "history_search.h"

typedef struct			s_fc
{
	int					l;
	int					n;
	int					num;
}						t_fc;

static int arrlen(char **query)
{
    int i;

    i = 0;
    while (query[i] != NULL)
        ++i;
    return (i);
}

static void      run_vi(char **environ)
{
    char    *str;
    char	**arg;

    str = ft_strjoin("vi ", "~/.42sh_history");
	str = replace_dir(str, environ);
	arg = write_arg(str);
	free(str);
	kazekage(arg);
    // init_history();
}

static int  check_query(char **query, t_fc *fc)
{
	int	i;
	int	j;

	i = 0;
	while(query[++i] != NULL)
	{
		if (query[i][0] != '-')
		{
			write(1, "fc: event not found\n", 21);
			return (-1);
		}
		j = 0;
		while (query[i][++j] != '\0')
		{
			if (query[i][j] == 'l' || query[i][j] == 'n' || (query[i][j] >= 48 && query[i][j] <= 57))
			{
				if (query[i][j] == 'l')
					fc->l = 1;
				else if (query[i][j] == 'n')
					fc->n = 1;
				else if (query[i][j] >= 48 && query[i][j] <= 57)
					fc->num = ft_atoi(&query[i][1]);
			}
			else
			{
				write(1, "fc: event not found\n", 21);
				return (-1);
			}
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

int     	shell_fc(t_process *proc)
{
    int     	qlen;
    char    	**query;
	t_fc		fc;

	init_fc(&fc);
    query = proc->query;
    qlen = arrlen(query);
    if (qlen == 1)
    {
        run_vi(g_sh->env);
        
    }
    else
    {
        if (check_query(query, &fc) == 0)
		{
			if (fc.l == 1)
			{
					print_history(g_h_session, fc.num, fc.n);
			}
		}
    }
    return (1);   
}
