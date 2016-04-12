/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/12 16:22:41 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static int	cd_move_path(t_list *environ,
						t_generic_options *options, char *curpath)
{
	if (ft_is_in(options->options, 'P') && !ft_is_in(options->options, 'L'))
	{
		if (*curpath == '/')
			curpath = ft_strfjoin(ft_strjoin(
				env_get(environ, "PWD"), "/"), curpath);
		return (builtin_cd_change_directory(&environ,
					curpath, 1));
	}
	else
		return (builtin_cd_change_directory(&environ, curpath, 0));
}

int			builtin_cd(t_list *environ, char **cmds)
{
	t_generic_options	options;
	char				*directory;
	char				*curpath;

	options = builtin_options_parser(cmds, "LP");
	if (!cmds[options.start] && ft_strcmp(cmds[options.start - 1], "-") == 0)
		options.start--;
	directory = cmds[options.start];
	if (!directory || ft_strcmp(cmds[options.start], "~") == 0)
		directory = builtin_cd_assert_home(environ);
	if (!directory)
		return (builtin_cd_error(0, ""));
	if (cmds[options.start] && ft_strcmp(cmds[options.start], "-") == 0)
		directory = env_get(environ, "OLDPWD");
	if (cmds[options.start] && cmds[options.start + 1])
	{
		directory = builtin_cd_assert_multiple_args(cmds, &options);
		if (!directory)
			return (1);
	}
	curpath = directory;
	return (cd_move_path(environ, &options, curpath));
}
