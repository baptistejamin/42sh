/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:24:29 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/11 20:00:40 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <libft.h>
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
	t_list			*env_list;
	int				last_res;
	t_list			*history;
	int				prompt_position;
	int				signals_disabled;
}					t_sh;

#endif
