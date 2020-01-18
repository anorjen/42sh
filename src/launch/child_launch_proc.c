/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_launch_proc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:58:09 by mgorczan          #+#    #+#             */
/*   Updated: 2020/01/18 13:24:37 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void		signal_default_changer(t_process *proc, t_job *job)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
	proc->pid = getpid();
	if (job->pgid > 0)
		setpgid(0, job->pgid);
	else
	{
		job->pgid = proc->pid;
		setpgid(0, job->pgid);
	}
}

void		pgid_and_dup_handle(t_process *proc, t_job *job,
		int in_fd, int out_fd)
{
	signal_default_changer(proc, job);

	if (in_fd != 0)
	{
		dup2(in_fd, 0);
		close(in_fd);
	}
	if (out_fd != 1)
	{
		dup2(out_fd, 1);
		close(out_fd);
	}
	if (proc->aggregate)
	{
		if (proc->aggregate->out == -1)
			close(proc->aggregate->in);
		else
		{
			if (proc->next != NULL)
				dup2(proc->aggregate->out, proc->aggregate->in);
		}
	}
}

void		child_launch_cycle(t_process *proc)
{
	if (execute_builtin_command(proc))
		exit(0);
	if (execve(proc->query[0], proc->query, g_sh->env) == -1)
	{
		phash_update();
		execve(phash_search(proc->query[0], HASH_FILES),
				proc->query, g_sh->env);
	}
}

void		child_launch_proc(t_job *job, t_process *proc,
		int in_fd, int out_fd)
{
	if (proc->aggregate && proc->aggregate->in == 2 && proc->aggregate->out == 1)
	{
		printf("%i, %i", proc->aggregate->in, proc->aggregate->out);
		exit(1);
	}
	pgid_and_dup_handle(proc, job, in_fd, out_fd);
	child_launch_cycle(proc);
	ft_printf("How u do it?\n", proc->query[0]);
	exit(1);
}
