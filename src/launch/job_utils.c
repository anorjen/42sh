/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 18:20:49 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/25 12:35:33 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int			release_job(int id)
{
	t_process	*proc;
	t_process	*tmp;
	t_job		*job_free;

	if (id > NR_JOBS || shell->jobs[id] == NULL)
		return (-1);
	job_free = shell->jobs[id];
	proc = job_free->root;
	while (proc != NULL)
	{
		tmp = proc->next;
//		free(proc->command);
//		free(proc->argv);
		free(proc->input_path);
		free(proc->output_path);
		free(proc);
		proc = tmp;
	}
//	free(job_free->command);
	free(job_free);
	return (0);
}

int			remove_job(int id)
{
	if (id > NR_JOBS || shell->jobs[id] == NULL)
		return (-1);
//	release_job(id);
	free(shell->jobs[id]);
	shell->jobs[id] = NULL;
	return (0);
}

int			get_job_id_by_pid(int pid)
{
	int		i;
	t_process	*proc;

	i = 0;
	while (++i <= NR_JOBS)
	{
		if (shell->jobs[i] != NULL)
		{
			proc = shell->jobs[i]->root;
			while (proc != NULL)
			{
				if (proc->pid == pid)
					return (i);
				proc = proc->next;
			}
		}
	}
	return (-1);
}

int			get_next_job_id(void)
{
	int		i;

	i = 0;
	while (++i <= NR_JOBS)
		if (shell->jobs[i] == NULL)
			return (i);
	return (-1);
}
