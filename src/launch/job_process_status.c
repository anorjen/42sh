/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_process_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 18:16:52 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/23 15:04:06 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	wait_for_job_ext(g_job_pid *job_pids, int id)
{
	while (job_pids->wait_count < job_pids->proc_count)
	{
		job_pids->wait_pid = waitpid(-shell->jobs[id]->pgid, &job_pids->status, WUNTRACED);
		kill(shell->jobs[id]->root->pid, SIGQUIT);
		job_pids->wait_count++;
//		printf("waitpid: %d | job_pids->status: %d\n", job_pids->wait_pid, job_pids->status);
		if (WIFEXITED(job_pids->status))
		{
			if ((job_pids->exit_status = WEXITSTATUS(job_pids->status)))
				shell->signal = job_pids->exit_status;
			set_process_status(job_pids->wait_pid, STATUS_DONE);
		}
		else if (WIFSIGNALED(job_pids->status))
			set_process_status(job_pids->wait_pid, STATUS_TERMINATED);
		else if (WSTOPSIG(job_pids->status))
		{
			job_pids->status = -1;
			set_process_status(job_pids->wait_pid, STATUS_SUSPENDED);
			if (job_pids->wait_count == job_pids->proc_count)
				print_job_status(id);
		}
		else
			set_process_status(job_pids->wait_pid, STATUS_DONE);
	}
	return (job_pids->status);
}

int				wait_for_job(int id)
{
	int			status;
	g_job_pid	*job_pids;

	job_pids = ft_memalloc(48);
	job_pids->status = 0;

	if (id > NR_JOBS || shell->jobs[id] == NULL)
		return (-1);
	job_pids->proc_count = get_proc_count(id, PROC_FILTER_REMAINING);
//	printf("proc count: %d \n", job_pids->proc_count);
	job_pids->wait_pid = -1;
	job_pids->wait_count = 0;
	status = wait_for_job_ext(job_pids, id);
	ft_memdel((void **)&job_pids);
	return (status);
}

int			get_proc_count(int id, int filter)
{
	int		count;
	process	*proc;

	if (id > NR_JOBS || shell->jobs[id] == NULL)
		return (-1);
	count = 0;
	proc = shell->jobs[id]->root;
	while (proc != NULL)
	{
		if (filter == PROC_FILTER_ALL ||
			(filter == PROC_FILTER_DONE && proc->status == STATUS_DONE) ||
			(filter == PROC_FILTER_REMAINING && proc->status != STATUS_DONE))
			count++;
//		printf("proc query: %s\n", proc->command);
		proc = proc->next;
	}
	return (count);
}

int			set_process_status(int pid, int status)
{
	int		i;
	process	*proc;

	i = 0;
	while (++i <= NR_JOBS)
	{
		if (shell->jobs[i] == NULL)
			continue;
		proc = shell->jobs[i]->root;
		while (proc != NULL)
		{
			if (proc->pid == pid)
			{
				proc->status = status;
				return (0);
			}
			proc = proc->next;
		}
	}
	return (-1);
}
