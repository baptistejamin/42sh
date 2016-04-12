/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/12 16:30:37 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int	builtin_pwd(t_list *environ, char **cmds)
{
	t_sh				*sh;
	char				path[PATH_MAX];
	t_generic_options	options;

	sh = t_sh_recover();
	options = builtin_options_parser(cmds, "LP");
	if (options.error)
	{
		ft_putstr_fd("bad option: -", 2);
		ft_putchar_fd(options.error_char, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	if (ft_is_in(options.options, 'P') && !ft_is_in(options.options, 'L') &&
		*env_get(environ, "PWD") == '/')
		ft_putendl(env_get(environ, "PWD"));
	else
	{
		getcwd(path, PATH_MAX);
		ft_putendl(path);
	}
	return (0);
}
