/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_segment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:13:28 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/24 14:37:50 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		get_mode(char *command)
{
	if (strcmp(command, "|") == 0)
		return COMMAND_PIPE;
	else if (strcmp(command, "<") == 0)
		return COMMAND_LREDIR;
	else if (strcmp(command, ">") == 0)
		return COMMAND_RREDIR;
	else if (strcmp(command, "<<") == 0)
		return COMMAND_HEREDOC;
	else if (strcmp(command, ">>") == 0)
		return COMMAND_APPEND;
	else
		return COMMAND_EXTERNAL;
}

int		is_agrarg(char *line)
{
	if (ft_strlen(line) == 4)
	{
		if (line[0] >= '0' && line[0] <= '2')
        {
            if (line[1] == '>' && line[2] == '&')
            {
                if ((line[3] >= '0' && line[3] <= '2') || line[3] == '-')
                    return (1);
            }
        }
	}
	return (0);
}

int	lenght_argproc(char **arg, int i)
{
	int lenght;

	lenght = 0;
	while (arg[i] && ft_strcmp(arg[i], "|"))
	{
		if (get_mode(arg[i]))
			++i;
        else if (!is_agrarg((arg[i])))
			++lenght;
		arg[i] ? ++i : 0;
	}
	return (lenght);
}

char    **new_query(char **arg, int i)
{
    char    **query;
	int     lenght;
    int     j;

    j = 0;
    if ((lenght = lenght_argproc(arg, i)) == 0)
	{
		ft_printf("Error\n");
		return (NULL);
	}
    if ((query = malloc(sizeof(char*) * (lenght + 1))) == NULL)
        exit(1);
    while (j < lenght)
    {
        if (get_mode(arg[i]))
			i += 2;
        else if (is_agrarg(arg[i]))
            ++i;
        query[j] = ft_strdup(arg[i]);
        ++j;
        if (!arg[i++])
            break ;
    }
    query[j] = NULL;
    return (query);
}

t_process *init_process(void)
{
    t_process *new_process;

    if ((new_process = (t_process*)malloc(sizeof(t_process))) == NULL)
        exit(1);
    new_process->query = NULL;
    new_process->output_file = NULL;
    new_process->output_path = NULL;
    new_process->output_mode = 0;
    new_process->heredoc = NULL;
    new_process->input_path = NULL;
    new_process->input_file = NULL;
    new_process->aggregate = NULL;
    new_process->pid = -1;
    new_process->type = 0;
    new_process->status = 0;
	new_process->next = NULL;
	return (new_process);
}



int         lenght_agrg(char **arg, int i)
{
    int lenght;

	lenght = 0;
	while (arg[i] && ft_strcmp(arg[i], "|"))
	{
		if (is_agrarg(arg[i]))
			++lenght;
        ++i;
	}
	return (lenght);
}

void        new_agregation(char **arg, int i, t_process *new_process)
{
    int lenght;

    lenght = lenght_agrg(arg, i);
    if (lenght == 0)
        return ;
    if ((new_process->aggregate = (t_aggregation*)malloc(sizeof(t_aggregation))) == NULL)
        exit(1);
    while (arg[i] && ft_strcmp(arg[i], "|"))
    {
        if (is_agrarg(arg[i]))
        {
            new_process->aggregate->in = arg[i][0] - 48;
            if (arg[i][3] == '-')
                new_process->aggregate->out = -1;
            else
                new_process->aggregate->out = arg[i][3] - 48;
        }
        ++i;
    }
}

t_process	*new_segment(char **arg, int i)
{
    t_process *new_process;
	int j;

	
    new_process = init_process();
    new_process->query = new_query(arg, i);
    if (!new_process->query)
        return (NULL);
    input_path(arg, i, new_process);
    output_path(arg, i, new_process);
    new_agregation(arg, i, new_process);


//    j = 0;
//    while (new_process->query && new_process->query[j])
//        ft_printf("query %s\n", new_process->query[j++]);
//    j = 0;
//    ft_printf("\n");
//    while (new_process->heredoc && new_process->heredoc[j])
//        ft_printf("heredoc %s\n", new_process->heredoc[j++]);
//       j = 0;
//    ft_printf("\n");
//    while (new_process->input_file && new_process->input_file[j])
//        ft_printf("redir %s\n", new_process->input_file[j++]);
//    ft_printf("\n");
//    if (new_process->input_path)
//        ft_printf("input_path %s\n", new_process->input_path);
//    ft_printf("---------------------\n");
//
//    j = 0;
//    while (new_process->output_file && new_process->output_file[j])
//        ft_printf("redir %s\n", new_process->output_file[j++]);
//    ft_printf("\n");
//    if (new_process->output_path)
//        ft_printf("output_path %s\n", new_process->output_path);
//    ft_printf("%i\n", new_process->output_mode);
//    ft_printf("\n");
//    if (new_process->aggregate)
//        ft_printf("in = %i out = %i\n", new_process->aggregate->in, new_process->aggregate->out);
	return (new_process);
}
