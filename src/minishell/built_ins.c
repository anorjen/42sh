/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:53:07 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/25 21:52:41 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int			help_shell(t_process *proc)
{
	int i;

	ft_printf("21shell of 21's school project\n");
	ft_printf("Built-in commands (input argument if needed):\n");
	i = 0;
	while (i < NR_BUILTINS)
	{
		ft_printf("\t -> %s\n", shell->builtins->builtin_str[i]);
		i++;
	}
	ft_printf("For additional info -> use \"man\".\n");
	return (1);
}

int			exit_shell(t_process *proc)
{
	printf(COLOR_MAGENTA "say-o-nara~\n" COLOR_NONE);
    exit(1);
//    return (1);
}


int			echo(t_process *proc)
{
    int i;

    i = 1;
    string_var_parser(proc->query);
    while (proc->query[i] != 0)
    {
        ft_printf("%s ", proc->query[i]);
        i++;
    }
    ft_printf("\n");
    return (1);
}



int			cd_shell(t_process *proc)
{
    if (proc->query[1] == NULL)
    {
        chdir(shell->pw_dir);
        sh_update_cwd_info();
        return (0);
    }
    if (chdir(proc->query[1]) == 0)
    {
        sh_update_cwd_info();
        return (0);
    }
    else
    {
        printf("21sh: cd %s: No such file or directory\n", proc->query[1]);
        return (0);
    }
}