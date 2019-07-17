//
// Created by Yoshiko Harwyn hoare on 2019-07-13.
//

#include "../../headers/minishell.h"

static int  wait_for_job_ext(int wait_count, int proc_count, int id, int wait_pid)
{
	int status;
	int	exit_status;

	status = 0;
	while (wait_count <= proc_count)
	{
		wait_pid = waitpid(-shell->jobs[id]->pgid, &status, WUNTRACED);
		wait_count++;
		if (WIFEXITED(status))
		{
			if ((exit_status = WEXITSTATUS(status)))
				shell->signal = exit_status;
			set_process_status(wait_pid, STATUS_DONE);
		}
		else if (WIFSIGNALED(status))
			set_process_status(wait_pid, STATUS_TERMINATED);
		else if (WSTOPSIG(status))
		{
			status = -1;
			set_process_status(wait_pid, STATUS_SUSPENDED);
			if (wait_count == proc_count)
				print_job_status(id);
		}
	}
	return (status);
}

int			wait_for_job(int id)
{
	int		proc_count;
	int		wait_pid;
	int		wait_count;
	int		status;

	if (id > NR_JOBS || shell->jobs[id] == NULL)
		return (-1);
	proc_count = get_proc_count(id, PROC_FILTER_REMAINING);
	wait_pid = -1;
	wait_count = 0;
	status = wait_for_job_ext(wait_count, proc_count, id, wait_pid);
	return (status);
}

int get_proc_count(int id, int filter)
{
	int		count;
	process	*proc;

	if (id > NR_JOBS || shell->jobs[id] == NULL)
		return (-1);
	count = 0;
	proc = shell->jobs[id]->root;
	while(proc != NULL)
	{
		if (filter == PROC_FILTER_ALL ||
			(filter == PROC_FILTER_DONE && proc->status == STATUS_DONE) ||
			(filter == PROC_FILTER_REMAINING && proc->status != STATUS_DONE)) {
			count++;
		}
		proc = proc->next;
	}
	return (count);
}


int set_process_status(int pid, int status)
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
