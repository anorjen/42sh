/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbearded <sbearded@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:41:11 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/10/27 11:22:18 by sbearded         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sh_init(char **environ)
{
	struct sigaction	sigint_action;
	pid_t				pid;
	struct passwd		*pw;
	int					i;

	g_input_mode = 0;
	g_env = NULL;
	sigint_action.sa_flags = 0;
	i = -1;
	sigint_action.sa_handler = &sigint_handler;
	sigemptyset(&sigint_action.sa_mask);
	sigaction(SIGINT, &sigint_action, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	pid = getpid();
	setpgid(pid, pid);
	tcsetpgrp(0, pid);
	g_sh = ft_memalloc(sizeof(t_shell_info));
	g_sh->env = init_environ(environ);
	getlogin_r(g_sh->cur_user, sizeof(g_sh->cur_user));
	pw = getpwuid(getuid());
	ft_strcpy(g_sh->pw_dir, pw->pw_dir);
	while (++i < NR_JOBS)
		g_sh->jobs[i] = NULL;
}

void		sh_print_promt(void)
{
	usleep(400);
	if (g_sh->signal == 0)
		ft_printf(COLOR_GREEN "⦿" COLOR_MAGENTA "  %s" COLOR_NONE " ",
				basename(g_sh->cur_dir));
	else
		ft_printf(COLOR_RED "⦿" COLOR_MAGENTA "  %s" COLOR_NONE " ",
				basename(g_sh->cur_dir));
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
	char						**args;
	int							status;
	t_job						*job;

	status = 1;
	g_h_session = NULL;
	set_termcap(env);
	job = NULL;
	while (status >= 0)
	{
		sh_print_promt();
		g_sh->signal = 0;
		args = parser(&g_h_session, env,
				ft_strlen(basename(g_sh->cur_dir)) + ft_strlen("⦿") + 1);
		if (parser_error_print(args))
			continue ;
		if (args == NULL)
		{
			check_zombie();
			continue ;
		}
		kazekage(args);
	}
}

int			main(int argc, char **argv, char **env)
{
	argc = 0;
	argv = NULL;
	sh_init(env);
	phash_init();
	sh_update_cwd_info();
	alias_init();
	shell_loop(env);
	return (0);
}
