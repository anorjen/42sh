/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:41:11 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/17 14:56:58 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
static struct termios	stored_settings;

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
//	printf(COLOR_YELLOW "21sh>" COLOR_NONE " ");
}

void	set_keypress(void)
{
	struct termios	new_settings;

	tcgetattr(0, &stored_settings);
	new_settings = stored_settings;
	new_settings.c_lflag &= (~ICANON & ~ECHO);
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &new_settings);
	return ;
}

void	reset_keypress(void)
{
	tcsetattr(0, TCSANOW, &stored_settings);
	return;
}

char		*get_termcap(char **environ)
{
	char	*term;
	char	*term_edit;
	
	if ((term = ft_strnew(2048)))
	{
		if ((term_edit = ft_strdup(getenv("TERM"))))
		{
			tgetent(term, term_edit);
			if (tgetent(term, term_edit) == 1)
			{
				free(term_edit);
				return (term);
			}
			free(term_edit);
		}
		free(term);
	}
	return (NULL);
}

void	set_termenv(char *termcap)
{
	term = (t_term *)malloc(sizeof(t_term));
	term->le = tgetstr("le", &termcap);
	term->nd = tgetstr("nd", &termcap);
	term->cd = tgetstr("cd", &termcap);
	term->dc = tgetstr("dc", &termcap);
	term->im = tgetstr("im", &termcap);
	term->ei = tgetstr("ei", &termcap);
	term->so = tgetstr("so", &termcap);
	term->se = tgetstr("se", &termcap);
	term->up = tgetstr("up", &termcap);
	term->do_ = tgetstr("do", &termcap);


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












void		shell_loop(char **env)
{
	char		*line;
	char		**args;
	job			*job;
	int			status;
	t_history_session *h_session;
	char	*termcap;


//	shell_init();
	sh_init();
	status = 1;
	h_session = NULL;
	if ((termcap = get_termcap(env)))
		set_termenv(termcap);
	set_keypress();
	while (status >= 0)
	{
		sh_print_promt();
		shell->signal = 0;
		args = parser(&h_session, env, ft_strlen(basename(shell->cur_dir)) + ft_strlen("⦿") + 1);
		if (args && !ft_strcmp(args[0], "end"))
			break ;
			int i = 0;
		while (args && args[i])
			free(args[i++]);
		free(args);
		// line = read_ln(); ///
// 		if (ft_strlen(line) == 0)
// 		{
// 			check_zombie();
// 			continue ;
// 		}
// //		char **ARG = parser();
// //		function()
// 		job = shell_parse_command(line);
// 		status = shell_launch_job(job);
	}
	reset_keypress();
	free_hsess(h_session);
	free(termcap);


	int i = 0;
	while (args && args[i])
		free(args[i++]);
	free(args);
	free(term);
}















int			main(int argc, char **argv, char **env)
{

	shell_loop(env);

	return (0);
}
