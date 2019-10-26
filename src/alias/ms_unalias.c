#include "alias.h"

int ms_unalias(t_process *proc)
{
	int i;

	i = 0;
	string_var_parser(proc->query);
	if (proc->query[1] == NULL)
	{
		ft_putendl_fd("lsh: not enough arguments", 2);
		return (1);
	}
	while (proc->query[++i])
	{
		alias_unset(proc->query[i]);
	}
	return (1);
}
