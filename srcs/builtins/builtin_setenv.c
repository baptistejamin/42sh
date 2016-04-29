/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/29 15:08:56 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static int	builtin_setenv_error_missing(void)
{
	ft_putendl_fd("setenv: You must provide an alphanumeric variable", 2);
	return (2);
}

static int	builtin_setenv_error_two_many(void)
{
	ft_putendl_fd("setenv: Two many arguments", 2);
	return (2);
}

int			builtin_setenv(t_list *environ, char **cmds)
{
	t_sh	*sh;
	char	*val;
	int		i;

	UNUSED(cmds);
	UNUSED(environ);
	sh = t_sh_recover();
	i = 0;
	if (!cmds[1])
		return (builtin_setenv_error_missing());
	if (cmds[2] && cmds[3])
		return (builtin_setenv_error_two_many());
	if (ft_strchr(cmds[1], '=') || (cmds[2] && ft_strchr(cmds[2], '=')))
		return (builtin_setenv_error_missing());
	val = cmds[2];
	if (!val)
		val = ft_strnew(1);
	env_set(&sh->env_list, cmds[1], val);
	return (0);
}
