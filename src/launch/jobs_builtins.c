/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 14:00:09 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/26 14:07:23 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int				shell_jobs(t_process *proc)
{
	int		i;

	i = -1;
	while (++i <= NR_JOBS)
	{
		if (shell->jobs[i] != NULL)
			print_job_status(i);
	}
	return (0);
}

int				set_job_status(int id, int status)
{
	t_process	*proc;

	if (id > NR_JOBS || shell->jobs[id] == NULL)
		return (-1);
	proc = shell->jobs[id]->root;
	while (proc != NULL)
	{
		if (proc->status != STATUS_DONE)
			proc->status = status;
		proc = proc->next;
	}
	return (0);
}

int				get_pgid_by_job_id(int id)
{
	t_job		*job;

	job = get_job_by_id(id);
	if (job == NULL)
		return (-1);
	return (job->pgid);
}

t_job			*get_job_by_id(int id)
{
	if (id > NR_JOBS)
		return (NULL);
	return (shell->jobs[id]);
}

int				wait_for_pid(int pid)
{
	int			status;

	status = 0;
	waitpid(pid, &status, WUNTRACED);
	if (WIFEXITED(status))
		set_process_status(pid, STATUS_DONE);
	else if (WIFSIGNALED(status))
		set_process_status(pid, STATUS_TERMINATED);
	else if (WSTOPSIG(status))
	{
		status = -1;
		set_process_status(pid, STATUS_SUSPENDED);
	}
	return (status);
}
