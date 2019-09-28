/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vi_input.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 14:01:48 by anorjen           #+#    #+#             */
/*   Updated: 2019/09/28 18:39:47 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VI_INPUT_H
# define VI_INPUT_H

// # include "main.h"
# include "libft.h"
# include "minishell.h"
# include "ft_dlist.h"
# include "ft_string.h"
# include "history_search.h"
# include <fcntl.h>
# include <term.h>

enum
{
	KC_TAB = 9,
	KC_NL = 10,
	KC_ESC = 27,
	KC_BS = 127,
	KC_DEL = 1295,
	KC_UP = 1183,
	KC_DOWN = 1184,
	KC_RIGHT = 1185,
	KC_LEFT = 1186,
	KC_HOME = 1190,
	KC_END = 1188,
	KC_CTRL_E = 5,
	KC_CTRL_R = 18,
	KC_CTRL_U = 21,
	KC_CTRL_D = 4,
	KC_NEXT_WORD = 1349,
	KC_PREV_WORD = 1351,
	KC_COPY = 1362,
	KC_PASTE = 1516,
	KC_CUT = 1499,
	RL_CTRL_B = 2,
	RL_CTRL_F = 6,
	RL_CTRL_P = 16,
	RL_CTRL_N = 14,
	RL_CTRL__ = 31,
	RL_CTRL_T = 20,
	RL_ALT_T = 1514
};

// typedef struct	s_tterm
// {
// 	char	*le;
// 	char	*nd;
// 	char	*cd;
// 	char	*dc;
// 	char	*im;
// 	char	*ei;
// 	char	*so;
// 	char	*se;
// }				t_tterm;

typedef struct	s_line
{
	char	*str;
	int		len;
	int		left;
	t_dlist	*edit_history;
}				t_line;

/*
** in_wait_input
*/
char			*wait_input();
t_line			*line_init();
void			line_deinit(t_line *line);
void			add_str_history(t_line *line, int key);
int				is_str(char *str);

/*
** in_wait_input_default
*/
t_line			*wait_input_default(t_line *line);
int				ft_read_keycode(int pm, t_line *line);
void			keycode_func(int key, t_line *line);
void			ft_print(t_line *line, char c);
void			listener(int sig);

/*
** in_wait_input_vi
*/
t_line			*wait_input_vi(t_line *line);

/*
** in_wait_input_rl
*/
t_line			*wait_input_rl(t_line *line);

/*
**	in_command_line
*/
int				is_arrow(int key);
void			ft_backspace(char **str, int *len, int left);
void			ft_delkey(char **str, int *len, int *left);
void			ft_clear_line(int len, int left);
void			ft_newline(t_line *line);

/*
**	in_ft_keys
*/
void			ft_keys(int key, char **line, int *len, int *left);
void			ft_key_home(int *len, int *left);
void			ft_key_end(int len, int *left);
void			ft_key_prev(char *line, int len, int *left);
void			ft_key_next(char *line, int len, int *left);

/*
**	in_arrows
*/
void			arrow_left(int len, int *left);
void			arrow_right(int *left);
void			arrow_up(char **str, int *len, int *left);
void			arrow_down(char **str, int	*len, int *left);
void			arrows(int key, char **str, int *len, int *left);

/*
**	in_ft_quotes
*/
void			ft_quotes(t_line *line);
int				is_quote(char c);
int				is_backslash(char *str, int i);

/*
**	in_ft_put
*/
int				ft_put(int c);

/*
**	in_bracket
*/
int				is_open_bracket(char c);
int				is_close_bracket(char open_bracket, char c);
int				find_close_quote(char *str, int i, char quote);
char			ft_find_bracket(char *str);


/*
**	############### edit_string ######################################
*/

/*
**	eh_ft_list_del
*/
void	ft_list_del(t_list **lst);

/*
**	eh_ft_undo
*/
void	ft_undo(t_line *line);

/*
**	############### copy_mode ########################################
*/

/*
**	cm_copy_mode
*/
void		ft_copy_mode(t_line *line);

/*
**	cm_func
*/
char		*ft_copy(char *line, int start_pos, int end_pos);
void		ft_paste(char **line, int *len, int *left, char *buf);
char		*ft_cut(char **line, int start_pos, int *len, int *left);

/*
**	###################### rl_mode #######################################################
*/
void		ft_swap_words(t_line *line);
void		ft_swap_chars(t_line *line);

/*
**	#####################################################################################
*/

t_dlist			*g_history;
int				g_input_line;
// t_tterm			*g_tterm;
char			g_vi_last[2];
int				g_input_mode;
char			*g_strbuf;


/*
**	################### vi_mode ##########################################################
*/

int				vi_a(t_line *line, int count);
int				vi_ab(t_line *line, int count);
int				vi_arr_up(t_line *line, int count);
int				vi_b(t_line *line, int count);
int				vi_c(t_line *line, int count);
int				vi_cb(t_line *line, int count);
int				vi_comma(t_line *line, int count);
int				vi_d(t_line *line, int count);
int				vi_db(t_line *line, int count);
int				vi_dollar(t_line *line, int count);
int				vi_e(t_line *line, int count);
int				vi_f(t_line *line, int count);
void			vi_f_do(t_line *line, int count, char c);
int				vi_fb(t_line *line, int count);
void			vi_fb_do(t_line *line, int count, char c);
int				vi_grill(t_line *line, int count);
int				vi_h(t_line *line, int count);
int				vi_i(t_line *line, int count);
int				vi_ib(t_line *line, int count);
int				vi_j(t_line *line, int count);
int				vi_k(t_line *line, int count);
int				vi_l(t_line *line, int count);
int				vi_p(t_line *line, int count);
int				vi_pb(t_line *line, int count);
int				vi_pipe(t_line *line, int count);
int				vi_r(t_line *line, int count);
int				vi_rb(t_line *line, int count);
int				vi_sb(t_line *line, int count);
int				vi_semicolon(t_line *line, int count);
int				vi_u(t_line *line, int count);
int				vi_ub(t_line *line, int count);
int				vi_v(t_line *line, int count);
int				vi_w(t_line *line, int count);
int				vi_x(t_line *line, int count);
int				vi_xb(t_line *line, int count);
int				vi_y(t_line *line, int count);
int				vi_yb(t_line *line, int count);
int				vi_zero(t_line *line, int count);

void			ft_delline(t_line *line, int start, int size);

typedef int	(*t_spe_key) (t_line *line, int count);

typedef struct	s_vi_actions
{
	t_spe_key	action;
	char		value;
}				t_vi_actions;


/*
**	########################################################################################
*/

#endif
