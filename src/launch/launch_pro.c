//
// Created by Yoshiko Harwyn hoare on 2019-07-02.
//

#include "../../headers/minishell.h"


static h_launch	*h_launch_init(void)
{
	h_launch *launch;

	launch = (h_launch *)malloc(sizeof(h_launch));
	launch->status = 0;
	launch->in_fd = 0;
	launch->out_fd = 1;
	launch->job_id = -1;
	launch->holder[0] = 0;
	ft_bzero(launch->holder, 48);

	return (launch);
}


void stdin_heredoc(t_process *proc,h_launch *launch, char *line)
{
	FILE	*fp;

	fp = fopen ("/tmp/stdin","w");
	fprintf (fp,"%s\n", line);
	fclose (fp);
	if (proc->input_path == NULL)
		proc->input_path = "/tmp/stdin";
}

char *str_join_her(char *s1, char *s2)
{
	char *temp;

	if (!s1)
	{
		if (s2)
			s1 = ft_strdup(s2);
		else
			return (ft_strdup("\n"));
	}
	else
	{
		if (s2)
		{
			temp = s1;
			s1 = ft_strjoin(s1, "\n");
			free(temp);
			temp = s1;
			s1 = ft_strjoin(s1, s2);
			free(temp);
		} else
		{
			temp = s1;
			s1 = ft_strjoin(s1, "\n");
			free(temp);
		}
	}
	return (s1);
}

char *readline_her(t_process *proc, int i)
{
	char *line;
	char *temp;
	t_history_session *h_session;

	line = NULL;
	temp = NULL;
	h_session = NULL;
	while(21)
	{
		h_session = add_history(h_session, ft_strlen("heredoc> "));
//		ft_printf("THIS\n");
		temp = input(&h_session, ft_strlen("heredoc> "), MODE_HEREDOC, shell->env);
		free_hsess(h_session);
		h_session = NULL;
		if (temp && !ft_strcmp(temp, proc->heredoc[i]))
			break ;
		line = str_join_her(line, temp);
		if (temp)
			free(temp);
	}

	return (line);
}


void launch_heredoc(t_process *proc, h_launch *launch)
{
	int i;
	char *line;

	i = 0;
	line = NULL;
	while (proc->heredoc && proc->heredoc[i])
	{
		if (line)
			free(line);
		line = readline_her(proc, i);
		++i;
	}
	stdin_heredoc(proc, launch, line);
}


int			check_access(char **files, int id)
{
	int i;

	i = 0;
	while (files[i])
	{
		if (access(files[i], F_OK) == -1)
		{
			printf("21sh: %s: No such file or directory\n", files[i]);
			remove_job(id);
			return (0);
		}
		++i;
	}
	return (1);
}

int 		pre_launch_config(t_process *proc, h_launch *launch)
{
	if (proc->heredoc == NULL)
	{
		if (check_access(proc->input_file, launch->job_id))
			launch->in_fd = open(proc->input_path, O_RDONLY);
		else
			return (0);
	}
	else
	{
		launch_heredoc(proc, launch);
		launch->in_fd = open(proc->input_path, O_RDONLY);
		if (proc->input_file)
			if (!check_access(proc->input_file, launch->job_id))
				return (0);
	}
	if (launch->in_fd < 0)
	{
		printf("21sh: no such file or directory: %s\n", proc->input_path);
		remove_job(launch->job_id);
		return (0);
	}
	else
		return (1);
}

int		launch_out_redir(t_process *proc, h_launch *launch)
{
	int i;

	i = 0;
	if (proc->output_file)
	{
		printf("fd: %d", launch->out_fd);
		while (proc->output_file[i])
		{
			if (proc->output_mode == 2)
			{
				if (access(proc->output_file[i], F_OK) == -1)
					launch->out_fd = open(proc->output_file[i], CREATE_ATTR);
				else
					launch->out_fd = open(proc->output_file[i], APPEND_ATTR);
			}
			else
				launch->out_fd = open(proc->output_file[i], CREATE_ATTR);
			if (launch->out_fd == -1)
			{
				printf("21sh: %s: Permission denied:\n", proc->output_file[i]);
				remove_job(launch->job_id);
				return (0);
			}
			printf("launch->fd: %d\n", launch->out_fd);
			++i;
			if (proc->output_file[i])
				close(launch->out_fd);
		}
	}
	return (1);
}

int		launch_base_config(h_launch *launch, t_process *proc, t_job *job)
{
	launch->out_fd = 1;
	if (proc->output_path != NULL)
	{
		if (!launch_out_redir(proc, launch))
			return (0);
	}
	launch->status = shell_launch_process(job, proc, launch->in_fd, launch->out_fd, job->mode);
	return (1);
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

static int		launch_proc_cycle(t_process *proc, h_launch *launch, t_job *job)
{
	while(proc != NULL)
	{
		if (proc == job->root && (proc->input_path != NULL || proc->heredoc !=NULL))
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
	t_process		*proc;
	h_launch	*launch;

	launch = h_launch_init();
	check_zombie();
	if (job->root->type == COMMAND_EXTERNAL)
		launch->job_id = insert_job(job);
	proc = job->root;
	launch->status = launch_proc_cycle(proc, launch, job);

	// BEWARE
	if (job->root->next)
		close(launch->in_fd);


	if (job->root->type == COMMAND_EXTERNAL)
	{
		if (launch->status >= 0 && job->mode == FOREGROUND_EXECUTION)
			remove_job(launch->job_id);
		else if (job->mode == BACKGROUND_EXECUTION)
			print_processes_of_job(launch->job_id);
	}
//	close(launch->out_fd);
//	close(launch->in_fd);
	print_holder(launch);
	clean_holder(launch);
	return (launch->status);
}

static void		pgid_and_dup_handle(t_process *proc, t_job *job, int in_fd, int out_fd)
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
	if (in_fd != 0)
	{
		dup2(in_fd, 0);
		close(in_fd);
	}
	if (out_fd != 1)
	{
//		printf("childe: out_fd: %d\n", out_fd);
		dup2(out_fd, 1);
		close(out_fd);
	}
	if (proc->aggregate)
	{
		if (proc->aggregate->out == -1)
			close(proc->aggregate->in);
		else
		{
//			printf("hi\n");
			printf("in_fd: %d out_fd: %d\n", in_fd, out_fd);
//			dup2(proc->aggregate->in, proc->aggregate->out);
//			dup2(0, 2);
//			close(proc->aggregate->out);
		}
	}
}

void 			child_launch_proc(t_job *job, t_process *proc, int in_fd, int out_fd)
{
	char 		*path;
	char 		**paths;
	int			i;

	i = 0;
	printf("0) in_fd: %d out_fd: %d\n", in_fd, out_fd);
	pgid_and_dup_handle(proc, job, in_fd, out_fd);
	paths = ft_strsplit(getenv("PATH"), ':');
	if (proc->next != NULL && proc->aggregate)
	{
		printf("A) in_fd: %d out_fd: %d\n", in_fd, out_fd);
		dup2(proc->aggregate->out, proc->aggregate->in);
//		close(proc->aggregate->out);
//		close(in_fd);
//		close(out_fd);
//		close(1);
//		close(2);
//		close(4);
		printf("1) in_fd: %d out_fd: %d\n", in_fd, out_fd);

//			printf("aggro: %d\n", proc->aggregate->out);
//			close(2);
	}
	while (paths[++i] != NULL)
	{

//		printf("in_fd: %d out_fd: %d\n", in_fd, out_fd);
		path = ft_strjoiner(paths[i], proc->query[0]);
		if (execve(path, proc->query, shell->env) != -1)
		{
			free(path);
			free(paths);
			exit(0);
		}
		free(path);
	}
	printf("21sh: %s: command not found\n", proc->query[0]);
	exit(1);
}

int				shell_launch_process(t_job *job, t_process *proc, int in_fd, int out_fd, int mode)
{
	pid_t		childpid;
	int			status;

	proc->status = STATUS_RUNNING;
	if (proc->type != COMMAND_EXTERNAL && execute_builtin_command(proc))
		return (0);
	status = 0;
	childpid = fork();
	if (childpid < 0)
		return (-1);
	else if (childpid == 0)
		child_launch_proc(job, proc, in_fd, out_fd);
	else
	{
		proc->pid = childpid;
		if (job->pgid > 0)
			setpgid(childpid, job->pgid);
		else
		{
			job->pgid = proc->pid;
			setpgid(childpid, job->pgid);
		}
		if (mode == FOREGROUND_EXECUTION)
		{
			tcsetpgrp(0, job->pgid);
			status = wait_for_job(job->id);
			signal(SIGTTOU, SIG_IGN);
			tcsetpgrp(0, getpid());
			signal(SIGTTOU, SIG_DFL);

			//watch

//			if (out_fd >= 3)
//				close(out_fd);

//			check_zombie();
		}
	}
	return (status);
}