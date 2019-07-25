/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:07:58 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/25 20:03:06 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int			len_two_dim(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char		*helper_strtrim(char *line)
{
	char	*head;
	char	*tail;

	head = line;
	tail = line + strlen(line) - 1;
	while (*head == ' ')
		head++;
	while (*tail == ' ')
		tail--;
	*(tail + 1) = '\0';
	return (head);
}

void		check_zombie(void)
{
	int		status;
	int		pid;
	int		job_id;

	while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0)
	{
		if (WIFEXITED(status))
			set_process_status(pid, STATUS_DONE);
		else if (WIFSTOPPED(status))
			set_process_status(pid, STATUS_SUSPENDED);
		else if (WIFCONTINUED(status))
			set_process_status(pid, STATUS_CONTINUED);
		job_id = get_job_id_by_pid(pid);
		if (job_id > 0 && is_job_completed(job_id))
		{
			print_job_status(job_id);
			remove_job(job_id);
		}
	}
}

int			execute_builtin_command(t_process *proc)
{
	if (proc->type == COMMAND_EXIT)
		exit_shell(proc);
	else if (proc->type == COMMAND_CD)
		cd_shell(proc);
	else if (proc->type == COMMAND_HELP)
		help_shell(proc);
	else if (proc->type == COMMAND_JOBS)
		shell_jobs(proc);
	else if (proc->type == COMMAND_FG)
		shell_fg(proc);
	else if (proc->type == COMMAND_BG)
		shell_bg(proc);
	else if (proc->type == COMMAND_KILL)
		shell_kill(proc);
	else
		return (0);
	return (1);
}

void		update_holder(h_launch *launch, int fd)
{
	int i;

	i = 0;
	if (fd >= 3)
	{
		while (launch->holder[i] != 0)
		{
			if (launch->holder[i] == fd)
				return;
			++i;
		}
		launch->holder[i] = fd;
	}
}

void		print_holder(h_launch *launch)
{
	int i;

	i = 0;
	while (launch->holder[i] != 0)
	{
		printf("%d --- fd in use: %d\n", i, launch->holder[i]);
		++i;
	}
}

void		clean_holder(h_launch *launch)
{
	int i;

	i = 0;
	while (launch->holder[i] != 0)
	{
		close(launch->holder[i]);
		i++;
	}
}