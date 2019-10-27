#include "minishell.h"

char *get_status(t_exp *exp)
{
    if (ft_strequ(exp->word, "") && ft_strequ(exp->param, ""))
        return (ft_itoa(g_sh->launch->status));
    else if (exp->param)
        return (ft_strdup(exp->env));
    else
    {
        parser_error_set("42sh: bad substitution");
        return (ft_strdup(" "));
    }
}
