/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:24:29 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/15 19:31:33 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <libft.h>
# include <prompt.h>
# include <builtins.h>
# include <unistd.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>

# define UNUSED(x) (void)(x)
# define PATH_MAX 4096

typedef struct		s_env
{
	char			*var;
	char			*value;
}					t_env;

typedef struct		s_sh
{
	int				prompt_enabled;
	char			*term_name;
	int				tty;
	t_termios		term;
	t_termios		default_term;
	t_winsize		win;
	t_list			*env_list;
	int				last_res;
	t_list			*history;
	int				prompt_position;
	t_prompt		*c_prompt;
	int				signals_disabled;
	pid_t			pgid;
}					t_sh;

t_sh				*t_sh_recover(void);
char				*env_get(t_list *list, char *var);
void				env_set(t_list **list, char *var, char *value);
void				env_show(t_list *list);
void				env_to_list(t_list **list, char **environ);
char				**env_from_list(t_list *list);

/*
** SIGNALS
*/
void				ignore_major_signals(void);
void				reset_major_signals(void);

#endif
