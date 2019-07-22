/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 19:18:37 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/07/21 19:35:37 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"


static char	*read_ln_ext(char *buffer, int pos, int c, int buffsize, char *eof)
{
	while (1)
	{
		c = getchar();
		if (c == '\n')
		{
			printf("%s\n", buffer);
			if (strcmp(buffer, "EOF") == 0)
				return (buffer);
			else
			{
				buffer = ft_memalloc(100);
				ft_bzero(buffer, BUFF_SIZE);
			}

		}
		else if (c == EOF)
		{
			ft_putstr("\nTerminated by user\n");
			return(buffer);
		}
		else
			buffer[pos] = c;
		pos++;
		if (pos >= buffsize)
		{
			buffsize += BUFF_LN;
			buffer = ft_realloc(buffer, pos, buffsize);
			if (!buffer)
				exit(-8);
		}
	}
}

char		*read_ln_heredoc(char *eof)
{
	int		pos;
	int		buffsize;
	char	*buffer;
	int		c;

	pos = 0;
	c = 0;
	buffsize = BUFF_LN;
	buffer = ft_memalloc(buffsize);
	if (!buffer)
	{
		ft_putendl_fd("minishell: couldn't allocate memory", 2);
		exit(-8);
	}
	return (read_ln_ext(buffer, pos, c, buffsize, eof));
}