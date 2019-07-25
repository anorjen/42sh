/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:41:11 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/25 14:39:24 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"


void sigint_handler(int signal)
{
	printf("\n");
}

void sh_update_cwd_info(void)
{
	getcwd(shell->cur_dir, sizeof(shell->cur_dir));
}

void   built_init(void)
{
    shell->builtins = (g_builtins*)malloc(sizeof(g_builtins));
    shell->builtins->builtin_func[0] = &cd_shell;
    shell->builtins->builtin_func[1] = &help_shell;
    shell->builtins->builtin_func[2] = &exit_shell;
    shell->builtins->builtin_func[3] = &echo;
    shell->signal = 0;
    ft_strcpy(shell->builtins->builtin_str[0], "cd");
    ft_strcpy(shell->builtins->builtin_str[1], "help");
    ft_strcpy(shell->builtins->builtin_str[2], "exit");
    ft_strcpy(shell->builtins->builtin_str[3], "echo");
    ft_strcpy(shell->builtins->builtin_str[4], "jobs");
    ft_strcpy(shell->builtins->builtin_str[5], "bg");
    ft_strcpy(shell->builtins->builtin_str[6], "fg");
    ft_strcpy(shell->builtins->builtin_str[7], "kill");
}

void sh_init()
{
	struct sigaction	sigint_action;
	pid_t				pid;
	struct passwd		*pw;
	int					i;
	extern char 		**environ;

	sigint_action.sa_flags = 0;
	i = -1;
	sigint_action.sa_handler = &sigint_handler;
	sigemptyset(&sigint_action.sa_mask);
	sigaction(SIGINT, &sigint_action, NULL);
	signal(SIGQUIT, SIG_IGN);
	// signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	pid = getpid();
	setpgid(pid, pid);
	tcsetpgrp(0, pid);
	shell = (shell_info*)malloc(sizeof(shell_info));
	shell->env = environ;
	getlogin_r(shell->cur_user, sizeof(shell->cur_user));
	pw = getpwuid(getuid());
	strcpy(shell->pw_dir, pw->pw_dir);
	while (++i < NR_JOBS)
		shell->jobs[i] = NULL;
	built_init();
	sh_update_cwd_info();
}

void sh_print_promt(void)
{
//	printf(COLOR_CYAN "%s" COLOR_NONE " in " COLOR_YELLOW "%s" COLOR_NONE "\n", shell->cur_user, shell->cur_dir);
	if (shell->signal == 0)
		ft_printf(COLOR_GREEN "⦿" COLOR_MAGENTA "  %s" COLOR_NONE " ", basename(shell->cur_dir));
	else
		ft_printf(COLOR_RED "⦿" COLOR_MAGENTA "  %s" COLOR_NONE " ", basename(shell->cur_dir));
}


void		free_hsess(t_history_session *h_session)
{
	t_history_session *temp;

	while (h_session)
	{
		h_session->victor->del(&h_session->victor);
		if (h_session->line)
			free(h_session->line);
		temp = h_session;
		h_session = h_session->up;
		free(temp);
	}
}










void		inf_process(t_process		*new_process)
{
	int j;
	int	i;

	i = 0;
	while (new_process)
	{
		ft_printf("\n\nprocess - %i\n---------------------\n", i++);
		j = -1;
		ft_printf("new_process->query[]: ");
   		while (new_process->query && new_process->query[++j])
        	ft_printf("%i) %s, ", j, new_process->query[j]);
		ft_printf("\n\n");		
		j = -1;
		ft_printf("new_process->heredoc[]: ");
		while (new_process->heredoc && new_process->heredoc[++j])
		    ft_printf("%i) %s,  ", j, new_process->heredoc[j]);
		ft_printf("\n");
		j = -1;
		ft_printf("new_process->input_file[]: ");
		while (new_process->input_file && new_process->input_file[++j])
		    ft_printf("%i) %s, ", j, new_process->input_file[j]);
		ft_printf("\n");		
		ft_printf("new_process->input_path: ");
		ft_printf("%s ", new_process->input_path);
		ft_printf("\n\n");
		j = -1;
		ft_printf("output_file: ");
		while (new_process->output_file && new_process->output_file[++j])
		    ft_printf("%i) %s, ", j, new_process->output_file[j]);
		ft_printf("\n");
		ft_printf("new_process->output_path: %s\n", new_process->output_path);
		ft_printf("new_process->output_mode %i\n\n", new_process->output_mode);
		ft_printf("\n\n");
		if (new_process->aggregate)
			ft_printf("new_process->aggregate: in = %i out = %i\n", new_process->aggregate->in, new_process->aggregate->out);
		new_process = new_process->next;
	}
	
    
}

void		shell_loop(char **env)
{
	char		**args;
	t_job		*job;
	int			status;
	t_history_session *h_session;

	sh_init();
	status = 1;
	h_session = NULL;


//	int i;
//	i = 0;
//	i = open("./hhh", CREATE_ATTR);
//	close(i);
//	i = open("./hhh", CREATE_ATTR);
//
//	printf("%d\n", i);



	while (status >= 0)
	{
		sh_print_promt();
		shell->signal = 0;

		args = parser(&h_session, env, ft_strlen(basename(shell->cur_dir)) + ft_strlen("⦿") + 1);
		if (args && !ft_strcmp(args[0], "exit"))
			break ;
		// int i = 0;
		// while (args && args[i])
		// 	ft_printf("%s\n", args[i++]);
		// ft_printf("\n\n");
		if (args == NULL)
			continue ;
		// inf_process(job->root);

		// // int i = 0;
		// // while (args && args[i])
		// // 	free(args[i++]);
		// // free(args);
		// // line = read_ln(); ///
		// if (ft_strlen(line) == 0)
		// {
		// 	check_zombie();
		// 	continue ;
		// }
		job = lexer(args);
//		inf_process(job->root);
		if (job)
			status = shell_launch_job(job);



	}

	free_hsess(h_session);


	// int i = 0;
	// while (args && args[i])
	// 	free(args[i++]);
	// free(args);
}















int			main(int argc, char **argv, char **env)
{

	shell_loop(env);

	return (0);
}
