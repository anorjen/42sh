/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_preconfig.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 23:19:30 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/25 23:19:30 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int 	pre_launch_config_case(h_launch *launch, t_process *proc)
{
	if (launch->in_fd < 0)
	{
		printf("21sh: no such file or directory: %s\n", proc->input_path);
		remove_job(launch->job_id);
		return (0);
	}
	else
		return (1);
}

int 		pre_launch_config(t_process *proc, h_launch *launch)
{
	if (proc->heredoc == NULL)
	{
		if (check_access(proc->input_file, launch->job_id))
		{
			launch->in_fd = open(proc->input_path, O_RDONLY);
			update_holder(launch, launch->in_fd);
		}
		else
			return (0);
	}
	else
	{
		launch_heredoc(proc, launch);
		launch->in_fd = open(proc->input_path, O_RDONLY);
		update_holder(launch, launch->in_fd);
		if (proc->input_file)
			if (!check_access(proc->input_file, launch->job_id))
				return (0);
	}
	return (pre_launch_config_case(launch, proc));
}


void		launch_pipe_config(t_process *proc, h_launch *launch, t_job *job)
{
	if (proc->output_path != NULL)
	{
		launch->out_fd = open(proc->output_path, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (launch->out_fd < 0)
			launch->out_fd = 1;
		launch->status = shell_launch_process(job, proc, launch->in_fd, launch->out_fd, PIPELINE_EXECUTION);
	}
	pipe(launch->fd);
	launch->status = shell_launch_process(job, proc, launch->in_fd, launch->fd[1], PIPELINE_EXECUTION);
	close(launch->fd[1]);
	launch->in_fd = launch->fd[0];
	update_holder(launch, launch->in_fd);
}
