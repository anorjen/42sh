
#ifndef MINISHELL_ALIAS_H
# define MINISHELL_ALIAS_H

# include "vector_lib.h"
// # include "../lib/printf/ft_printf.h"
#include "minishell.h"

char			**g_alias;
t_vector_lib	*g_alias_key;
t_vector_lib	*g_alias_value;

void	alias_deinit(void);
char	*alias_get(char *key);
void	alias_init(void);
void	alias_print(void);
void	alias_set(char *key, char *value);
void	alias_unset(char *key);
void	alias_update(void);
int		ms_alias(t_process *proc);
int		ms_unalias(t_process *proc);

#endif
