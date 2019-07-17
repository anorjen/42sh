//
// Created by Yoshiko Harwyn hoare on 2019-07-03.
//

#include "minishell.h"

int			release_job(int id)
{
	job		*job;
	process	*proc;
	process	*tmp;

	if (id > NR_JOBS || shell->jobs[id] == NULL)
		return -1;
	job = shell->jobs[id];
	proc = job->root;
	while (proc != NULL)
	{
		tmp = proc->next;
		free(proc->command);
		free(proc->argv);
		free(proc->input_path);
		free(proc->output_path);
		free(proc);
		proc = tmp;
	}
	free(job->command);
	free(job);
	return (0);
}


int			remove_job(int id)
{
	if (id > NR_JOBS || shell->jobs[id] == NULL)
		return -1;
	release_job(id);
	shell->jobs[id] = NULL;

	return (0);
}

int			get_job_id_by_pid(int pid)
{
	int		i;
	process	*proc;

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

int			insert_job(job *job)
{
	int id;

	id = get_next_job_id();
	if (id < 0)
		return (-1);
	job->id = id;
	shell->jobs[id] = job;
	return (id);
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

int			is_job_completed(int id)
{
	process *proc;

	if (id > NR_JOBS || shell->jobs[id] == NULL)
		return (0);
	proc = shell->jobs[id]->root;

	while (proc != NULL)
	{
		if (proc->status != STATUS_DONE)
			return (0);
		proc = proc->next;
	}
	return (1);
}

int			print_processes_of_job(int id)
{
	process	*proc;

	if (id > NR_JOBS || shell->jobs[id] == NULL)
		return -1;
	printf("[%d]", id);
	proc = shell->jobs[id]->root;
	while (proc != NULL)
	{
		printf(" %d", proc->pid);
		proc = proc->next;
	}
	printf("\n");
	return (0);
}


static char 	*get_state_string(process *proc)
{
	char		*state;

	if (proc->status == 0)
		state = strdup("running");
	else if (proc->status == 1)
		state = strdup("done");
	else if (proc->status == 2)
		state = strdup("suspended");
	else if (proc->status == 1)
		state = strdup("continued");
	else
		state = strdup("terminated");

	return (state);
}


int				print_job_status(int id)
{
	process *proc;
	char 	*state;

	if (id > NR_JOBS || shell->jobs[id] == NULL)
		return (-1);
	printf("[%d]", id);
	proc = shell->jobs[id]->root;
	while (proc != NULL)
	{
		state = get_state_string(proc);
		printf("\t%d\t%s\t%s", proc->pid,
			  state, proc->command);
		if (proc->next != NULL)
			printf("|\n");
		else
			printf("\n");
		proc = proc->next;
		free(state);
	}
	return (0);
}