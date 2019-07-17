//
// Created by Yoshiko Harwyn hoare on 2019-07-13.
//

#include "minishell.h"

int			shell_jobs(process *proc)
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

static int 	shell_fg_ext(pid_t pid, int job_id)
{
	if (kill(-pid, SIGCONT) < 0)
	{
		printf("mysh: fg %d: job not found\n", pid);
		return (-1);
	}
	tcsetpgrp(0, pid);
	if (job_id > 0)
	{
		set_job_status(job_id, STATUS_CONTINUED);
		print_job_status(job_id);
		if (wait_for_job(job_id) >= 0)
			remove_job(job_id);
	}
	else
		wait_for_pid(pid);
	signal(SIGTTOU, SIG_IGN);
	tcsetpgrp(0, getpid());
	signal(SIGTTOU, SIG_DFL);
	return (0);
}

int			shell_fg(process *proc)
{
	int		status;
	pid_t	pid;
	int		job_id;

	job_id = -1;
	if (proc->argc < 2)
	{
		printf("usage: fg <pid>\n");
		return (-1);
	}
	if (proc->argv[1][0] == '%')
	{
		job_id = atoi(proc->argv[1] + 1);
		pid = get_pgid_by_job_id(job_id);
		if (pid < 0)
		{
			printf("mysh: fg %s: no such job\n", proc->argv[1]);
			return (-1);
		}
	}
	else
		pid = atoi(proc->argv[1]);
	return (shell_fg_ext(pid, job_id));
}

static int	shell_bg_ext(pid_t pid, int job_id)
{
	if (kill(-pid, SIGCONT) < 0)
	{
		printf("mysh: bg %d: job not found\n", pid);
		return (-1);
	}
	if (job_id > 0)
	{
		set_job_status(job_id, STATUS_CONTINUED);
		print_job_status(job_id);
	}
	return (0);
}

int			shell_bg(process *proc)
{
	pid_t	pid;
	int		job_id;

	job_id = -1;
	if (proc->argc < 2)
	{
		printf("usage: bg <pid>\n");
		return (-1);
	}
	if (proc->argv[1][0] == '%')
	{
		job_id = atoi(proc->argv[1] + 1);
		pid = get_pgid_by_job_id(job_id);
		if (pid < 0)
		{
			printf("mysh: bg %s: no such job\n", proc->argv[1]);
			return (-1);
		}
	}
	else
		pid = atoi(proc->argv[1]);
	return (shell_bg_ext(pid, job_id));
}

static int	shell_kill_ext(pid_t pid, int job_id)
{
	if (kill(pid, SIGKILL) < 0)
	{
		printf("mysh: kill %d: job not found\n", pid);
		return (0);
	}
	if (job_id > 0) {
		set_job_status(job_id, STATUS_TERMINATED);
		print_job_status(job_id);
		if (wait_for_job(job_id) >= 0)
			remove_job(job_id);
	}
	return (1);
}

int			shell_kill(process *proc)
{
	pid_t	pid;
	int		job_id;

	if (proc->argc < 2)
	{
		printf("usage: kill <pid>\n");
		return (-1);
	}
	job_id = -1;
	if (proc->argv[1][0] == '%')
	{
		job_id = atoi(proc->argv[1] + 1);
		pid = get_pgid_by_job_id(job_id);
		if (pid < 0)
		{
			printf("mysh: kill %s: no such job\n", proc->argv[1]);
			return (-1);
		}
		pid = -pid;
	}
	else
		pid = atoi(proc->argv[1]);
	return(shell_kill_ext(pid, job_id));
}



int			set_job_status(int id, int status)
{
	int		i;
	process	*proc;

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

int			get_pgid_by_job_id(int id)
{
	job		*job;

	job = get_job_by_id(id);
	if (job == NULL)
		return (-1);
	return (job->pgid);
}

job			*get_job_by_id(int id)
{
	if (id > NR_JOBS)
		return NULL;
	return (shell->jobs[id]);
}

int			wait_for_pid(int pid)
{
	int		status;

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