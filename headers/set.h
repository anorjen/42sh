#ifndef INC_42SH_SET_H
#define INC_42SH_SET_H

# include "vector_lib.h"
# include "minishell.h"

char            **g_set;
t_vector_lib    *g_set_key;
t_vector_lib	*g_set_value;

void	set(char *key, char *value);
int		set_deinit(void);
int		set_init();
void	set_update(void);
void	unset(char *key);
void	set_print(void);
char	*set_get(char *key);
char	**ft_strsplit_first_char(char *str, char c);
int     ft_replace_set(t_process *proc);
void	ft_mas_del(char **mas);
int     ms_set(t_process *proc);
int     ms_unset(t_process *proc);
int     ms_export(t_process *proc);

#endif
