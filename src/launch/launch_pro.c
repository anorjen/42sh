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


int			check_access(char **files)
{
	int i;

	i = 0;
	while (files[i])
	{
		if (access(files[i], F_OK) == -1)
		{
			printf("21sh: %s: No such file or directory\n", files[i]);
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
		if (check_access(proc->input_file))
			launch->in_fd = open(proc->input_path, O_RDONLY);
		else
		{
			remove_job(launch->job_id);
			return (0);
		}
	}
	else
	{
		launch_heredoc(proc, launch);
		launch->in_fd = open(proc->input_path, O_RDONLY);
		if (proc->input_file)
			if (!check_access(proc->input_file))
			{
				remove_job(launch->job_id);
				return (0);
			}
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


void		launch_base_config(h_launch *launch, t_process *proc, t_job *job)
{
	launch->out_fd = 1;
	if (proc->output_path != NULL)
	{
		if (proc->output_mode == APPEND)
		{
			if (access(proc->output_path, F_OK) != -1)
				launch->out_fd = open(proc->output_path, O_APPEND |O_WRONLY, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
			else
				launch->out_fd = open(proc->output_path, CREATE_ATTR);
		}
		else
		{
			launch->out_fd = open(proc->output_path, CREATE_ATTR);
		}
		if (launch->out_fd < 0)
			launch->out_fd = 1;
	}
	launch->status = shell_launch_process(job, proc, launch->in_fd, launch->out_fd, job->mode);
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
			launch_base_config(launch, proc, job);
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
	if (job->root->type == COMMAND_EXTERNAL)
	{
		if (launch->status >= 0 && job->mode == FOREGROUND_EXECUTION)
			remove_job(launch->job_id);
		else if (job->mode == BACKGROUND_EXECUTION)
			print_processes_of_job(launch->job_id);
	}
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
	if (in_fd != 0) {
		dup2(in_fd, 0);
		close(in_fd);
	}
	if (out_fd != 1)
	{
		dup2(out_fd, 1);
		close(out_fd);
	}
}

void 			child_launch_proc(t_job *job, t_process *proc, int in_fd, int out_fd)
{
	char 		*path;
	char 		**paths;
	int			i;

	i = 0;
	pgid_and_dup_handle(proc, job, in_fd, out_fd);
	paths = ft_strsplit(getenv("PATH"), ':');
	while (paths[++i] != NULL)
	{
//		if (proc->aggregate->out == -1)
//		{
//			printf("aggro: %d\n", proc->aggregate->out);
//			close(2);
//		}
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
//			check_zombie();
		}
	}
	return (status);
}