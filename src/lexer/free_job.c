/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:44:09 by mgorczan          #+#    #+#             */
/*   Updated: 2019/07/25 15:24:51 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	*free_process(t_process *proc)
{
	int	i;

	i = 0;
	while (proc->query && proc->query[i])
		free(proc->query[i++]);
	if (proc->query)
		free(proc->query);
	i = 0;
	while (proc->heredoc && proc->heredoc[i])
		free(proc->heredoc[i++]);
	if (proc->heredoc)
		free(proc->heredoc);
	i = 0;
	while (proc->input_file && proc->input_file[i])
		free(proc->input_file[i++]);
	if (proc->input_file)
		free(proc->input_file);
	if (proc->input_path)
		free(proc->input_path);
	if (proc->aggregate)
		free(proc->aggregate);
	i = 0;
	while (proc->output_file && proc->output_file[i])
		free(proc->output_file[i++]);
	if (proc->output_file)
		free(proc->output_file);
	if (proc->output_path)
		free(proc->output_path);
	free(proc);
	return (NULL);
}

void	*free_job(t_job *job)
{
	t_process	*temp;

	if (!job)
		return (NULL);
	while (job->root)
	{
		temp = job->root;
		job->root = job->root->next;
		free_process(temp);
	}
	free(job);
	return (NULL);
}
