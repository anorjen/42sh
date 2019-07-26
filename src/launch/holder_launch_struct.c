/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   holder_launch_struct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 22:44:23 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/26 15:32:45 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int				check_access(char **files, int id)
{
	int			i;

	i = 0;
	while (files[i])
	{
		if (access(files[i], F_OK) == -1)
		{
			ft_printf("21sh: %s: No such file or directory\n", files[i]);
			remove_job(id);
			return (0);
		}
		++i;
	}
	return (1);
}

void			update_holder(h_launch *launch, int fd)
{
	int			i;

	i = 0;
	if (fd >= 3)
	{
		while (launch->holder[i] != 0)
		{
			if (launch->holder[i] == fd)
				return ;
			++i;
		}
		launch->holder[i] = fd;
	}
}

void			print_holder(h_launch *launch)
{
	int			i;

	i = 0;
	while (launch->holder[i] != 0)
	{
		ft_printf("%d --- fd in use: %d\n", i, launch->holder[i]);
		++i;
	}
}

void			clean_holder(h_launch *launch)
{
	int			i;

	i = 0;
	while (launch->holder[i] != 0)
	{
		close(launch->holder[i]);
		i++;
	}
}

h_launch		*h_launch_init(void)
{
	h_launch	*launch;

	launch = (h_launch *)malloc(sizeof(h_launch));
	launch->status = 0;
	launch->in_fd = 0;
	launch->out_fd = 1;
	launch->job_id = -1;
	launch->holder[0] = 0;
	ft_bzero(launch->holder, 48);
	return (launch);
}
