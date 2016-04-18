/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:24:29 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/18 19:15:26 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <shell.h>

typedef int	(*t_func)(t_list *environ, char **cmds);

typedef struct		s_builtin
{
	char			*name;
	t_func			func;
}					t_builtin;

typedef struct		s_generic_options
{
	char			options[256];
	int				start;
	int				error;
	int				error_char;
	int				options_counter;
}					t_generic_options;

int					builtin_exit(t_list *environ, char **cmds);
int					builtin_help(t_list *environ, char **cmds);
int					builtin_pwd(t_list *environ, char **cmds);
int					builtin_cd(t_list *environ, char **cmds);
int					builtin_env(t_list *environ,
									char **cmds);
int					builtin_setenv(t_list *environ, char **cmds);
int					builtin_unsetenv(t_list *environ,
								char **cmds);
void				builtin_unsetenv_free(void *content, size_t content_size);
int					is_builtin(char **cmds);
int					boot_builtin(t_list *environ, char **cmds);
int					boot_cmd(t_list *environ, char **cmds);
void				errors_is_directory(char *cmd);
void				errors_not_found(char *cmd);
void				errors_no_file_directory(char *cmd);
t_generic_options	builtin_options_parser(char **cmds,
							char *managed_options);
int					builtin_cd_change_directory(
						t_list **environ, char *curpath, int is_physical);
void				builtin_cd_update_path(
							t_list **environ, char *old_path, char *path);
char				*builtin_cd_assert_multiple_args(
							char **cmds, t_generic_options *options);
char				*builtin_cd_assert_home(t_list *environ);
int					builtin_cd_error(int type, char *path);
int					env_boot(t_list *environ, char **cmds);
int					env_launch_cmd(t_list *environ, char *cmd,
					char **args);
void				errors_is_directory(char *cmd);
void				errors_not_found(char *cmd);
void				errors_no_file_directory(char *cmd);
int					builtin_jobs(t_list *environ, char **av);

#endif
