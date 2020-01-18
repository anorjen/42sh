/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_pro.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:59:00 by mgorczan          #+#    #+#             */
/*   Updated: 2020/01/18 19:21:22 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				launch_proc_cycle(t_process *proc, t_launch *launch, t_job *job)
{
	while (proc != NULL)
	{
		if (proc == job->root &&
		(proc->input_path != NULL || proc->heredoc != NULL))
			if (!pre_launch_config(proc, launch))
				return (0);
		if (proc->next != NULL)
			launch_pipe_config(proc, launch, job);
		else
		{
			if (!launch_base_config(launch, proc, job))
				return (0);
		}
		proc = proc->next;
	}
	return (launch->status);
}

int				shell_launch_job(t_job *job)
{
	t_process	*proc;

	if (g_sh->launch)
		free(g_sh->launch);
	g_sh->launch = h_launch_init();
	check_zombie();
	g_sh->launch->job_id = insert_job(job);
	proc = job->root;
	g_sh->launch->status = launch_proc_cycle(proc, g_sh->launch, job);
	if (job->root->type == COMMAND_EXTERNAL ||
		job->root->type != COMMAND_EXTERNAL)
	{
		if (g_sh->launch->status >= 0 && job->mode == FOREGROUND_EXECUTION)
			remove_job(g_sh->launch->job_id);
		else if (job->mode == BACKGROUND_EXECUTION)
			print_processes_of_job(g_sh->launch->job_id);
	}
	if (DEBUG_LOG)
		print_holder(g_sh->launch);
	clean_holder(g_sh->launch);
	return (g_sh->launch->status);
}

void			parent_launch_process(t_process *proc,
										t_job *job, pid_t childpid)
{
	proc->pid = childpid;
	if (job->pgid > 0)
		setpgid(childpid, job->pgid);
	else
	{
		job->pgid = proc->pid;
		setpgid(childpid, job->pgid);
	}
}

int				check_built_in(t_process *proc)
{
	if (ft_strequ(proc->query[0], "exit")
		|| ft_strequ(proc->query[0], "cd")
		|| ft_strequ(proc->query[0], "setenv")
		|| ft_strequ(proc->query[0], "unsetenv")
		|| ft_strequ(proc->query[0], "jobs")
		|| ft_strequ(proc->query[0], "bg")
		|| ft_strequ(proc->query[0], "fg")
		|| ft_strequ(proc->query[0], "kill")
		|| ft_strequ(proc->query[0], "alias")
		|| ft_strequ(proc->query[0], "unalias")
		|| ft_strequ(proc->query[0], "set")
		|| ft_strequ(proc->query[0], "unset")
		|| ft_strequ(proc->query[0], "export")
		|| ft_strequ(proc->query[0], "fc")
		|| ft_strequ(proc->query[0], "echo"))
		return (1);
	else
		return (0);
}

int				shell_launch_process(t_job *job, t_process *proc,
			int in_fd, int out_fd)
{
	pid_t		childpid;
	int			status;

	proc->status = STATUS_RUNNING;
	proc->out_fdpipe = out_fd;
	if (is_sets(proc))
		return (add2set(proc));
	proc->query = ft_replace_set(proc);
	if (check_built_in(proc))
		return (!execute_builtin_command(proc));
	status = 0;
	if (fork_after_check_exist(proc))
		return (1);
	if ((childpid = fork()) < 0)
		return (-1);
	else if (childpid == 0)
		child_launch_proc(job, proc, in_fd, out_fd);
	else
	{
		parent_launch_process(proc, job, childpid);
		if (proc->exec_mode == FOREGROUND_EXECUTION)
		{
			tcsetpgrp(0, job->pgid);
			status = wait_for_job(job->id);
			SIG_PROC;
			signal(SIGTTOU, SIG_DFL);
		}
	}
	return (status);
}
