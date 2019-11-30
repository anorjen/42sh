/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 18:20:16 by rwalder-          #+#    #+#             */
/*   Updated: 2019/11/30 18:20:18 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set.h"

static int ft_array_len(char **array)
{
    int i;
    i = 0;
    while (array[i] != NULL)
        i++;
    return (i);
}

int     is_sets(t_process *proc)
{
    int i;
    char	**arr;

    i = -1;
    while (proc->query[++i])
    {
        if ((arr = ft_strsplit_first_char(proc->query[i], '=')) == NULL)
            return (0);
        ft_mas_del(arr);
    }
    return (1);
}

int     add2set(t_process *proc)
{
    char	**arr;
    int     i;

    i = -1;
    while (proc->query[++i])
    {
        if ((arr = ft_strsplit_first_char(proc->query[i], '=')) == NULL)
            continue ;
        set(arr[0], arr[1]);
        ft_mas_del(arr);
    }
    proc->type = 1;
    return (1);
}



void copy_env(void)
{
    int i;

    if (g_env_copy)
        return ;
    g_env_copy = ft_memalloc(sizeof(char *) * (ft_array_len(g_sh->env) + 1));
    i = 0;
    while (g_sh->env[i])
    {
        g_env_copy[i] = ft_strdup(g_sh->env[i]);
        i++;
    }
}

char	**ft_replace_set(t_process *proc)
{
    char	**arr;
    int     i;
    char    **new_query;
    int     array_counter;

    i = 0;
    array_counter = 0;
    new_query = ft_memalloc(sizeof(char *) * (ft_array_len(proc->query) + 1));
    while (proc->query[i])
    {
        if ((arr = ft_strsplit_first_char(proc->query[i], '=')) == NULL)
            break ;
        copy_env();
        set_env(arr[0], arr[1]);
        ft_mas_del(arr);
        ft_strdel(&(proc->query[i]));
        i++;
    }
    while (proc->query[i])
        new_query[array_counter++] = proc->query[i++];
    ft_memdel((void **)&(proc->query));
    return (new_query);
}
