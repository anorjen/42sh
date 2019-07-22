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
	launch->job_id = -1;

	return (launch);
}



//int launch_heredoc(job *job, process *proc,h_launch *launch)
//{
//	pid_t	rdr;  /* input reader process */
//	pid_t	cmd;  /* command runner process */
//	pid_t	wres; /* wait() result */
//
//	/* pipe for passing input from rdr to cmd */
//	int pipefd[2] = {0};
//	/* command and args to pass to execvp() */
//	char *command = "ls";
//	char *cmdargs[] = { "ls", "-l", NULL };
//	/* end of input marker */
//	char *endinp = "END\n";
//
//	/* create a pipe:
//	   - read end's fd will be pipefd[0],
//	   - write end's fd will be pipefd[1] */
//	pipe(pipefd);
//
//	cmd = fork();
//	if (cmd == 0) {  /* COMMAND RUNNER PROCESS */
//		dup2(pipefd[0],0); /* set stdin to pipe's read end */
//		close(pipefd[1]);  /* close pipe's write end */
//		/* exec command (will read from stdin) */
//		execvp(command, cmdargs);
//	}
//
//	rdr = fork();
//	if (rdr == 0) {   /* INPUT READER PROCESS */
//		close(pipefd[0]); /* close pipe's read end */
//
//		/* read input from stdin until a line containing only
//		   the end of input marker is found */
//		char buf[1024];
//		while (fgets(buf,sizeof(buf),stdin)) {
//			/* break when end of input marker is read */
//			if (!strcmp(buf,endinp)) break;
//			/* write data to pipe */
//			write(pipefd[1],buf,strlen(buf));
//		}
//		exit(0);
//	}
//
//	/* PARENT PROCESS */
//
//	close(pipefd[0]); /* close pipe's read end */
//	close(pipefd[1]); /* close pipe's write end */
//
//	/* wait for both children to exit */
//	do {
//		wres = wait(NULL);
//		if (wres == rdr) rdr = 0;
//		if (wres == cmd) cmd = 0;
//	} while (rdr || cmd);
//
//	return(0);
//}

void launch_heredoc(job *job, process *proc,h_launch *launch)
{
	char *str;

	while (ft_strcmp(str = read_ln(), proc->input_path))
		;
//	printf("%s\n", str);
	proc->heredoc = str;
//	launch->out_fd = open("/tmp/stdin", O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
	FILE * fp;
	fp = fopen ("/tmp/stdin","w");
	fprintf (fp,"%s\n", str);
	fclose (fp);
	proc->input_path = "/tmp/stdin";
//	printf("%s", proc->output_path);
//	exit(2);
//	proc->ou
//	return(0);
}


static int		launch_proc_cycle(process *proc, h_launch *launch, job *job)
{
	while(proc != NULL)
	{
		if (proc == job->root && proc->input_path != NULL)
		{
			if (proc->type != HEREDOC_EXECUTION)
				launch->in_fd = open(proc->input_path, O_RDONLY);
			else
			{
				launch_heredoc(job, proc, launch);
				launch->in_fd = open(proc->input_path, O_RDONLY);
//				return (launch->status);
			}
			if (launch->in_fd < 0)
			{
				printf("21sh: no such file or directory: %s\n", proc->input_path);
				remove_job(launch->job_id);
				return (0);
			}
		}
		if (proc->next != NULL)
		{
			if (proc->output_path != NULL)
			{
				launch->out_fd = open(proc->output_path, O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
				if (launch->out_fd < 0)
					launch->out_fd = 1;
				launch->status = shell_launch_process(job, proc, launch->in_fd, launch->out_fd, PIPELINE_EXECUTION);
			}
			pipe(launch->fd);
			launch->status = shell_launch_process(job, proc, launch->in_fd, launch->fd[1], PIPELINE_EXECUTION);
			close(launch->fd[1]);
			launch->in_fd = launch->fd[0];
		}
		else
		{
			launch->out_fd = 1;
			if (proc->output_path != NULL)
			{
				launch->out_fd = open(proc->output_path, O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
				if (launch->out_fd < 0)
					launch->out_fd = 1;
			}
			launch->status = shell_launch_process(job, proc, launch->in_fd, launch->out_fd, job->mode);
		}
		proc = proc->next;
	}
	return (launch->status);
}

static void print2dim(char **argv)
{
	while (*argv++)
		printf("%s\n", *argv);
}

int				shell_launch_job(job *job)
{
	process		*proc;
	h_launch	*launch;

	launch = h_launch_init();
	check_zombie();
	if (job->root->type == COMMAND_EXTERNAL || job->root->type == HEREDOC_EXECUTION)
		launch->job_id = insert_job(job);
	proc = job->root;
//	print2dim(shell->jobs[1]->root->argv); //remove it
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

static void		pgid_and_dup_handle(process *proc, job *job, int in_fd, int out_fd)
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

void 			child_launch_proc(job *job, process *proc, int in_fd, int out_fd)
{
	char 		*path;
	char 		**paths;
	int			i;

	i = 0;
	pgid_and_dup_handle(proc, job, in_fd, out_fd);
	paths = ft_strsplit(getenv("PATH"), ':');
	while (paths[++i] != NULL)
	{
		path = ft_strjoiner(paths[i], proc->argv[0]);
		if (execve(path, proc->query, shell->env) != -1)
		{
			free(path);
			free(paths);
			exit(0);
		}
		free(path);
	}
	printf("21sh: %s: command not found\n", proc->argv[0]);
	exit(1);
}

int				shell_launch_process(job *job, process *proc, int in_fd, int out_fd, int mode)
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
		}
	}
	return (status);
}