/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/18 22:46:34 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static t_builtin	*builtins_get(void)
{
	static t_builtin	f[] = {
		{"pwd", builtin_pwd},
		{"exit", builtin_exit},
		{"cd", builtin_cd},
		{"env", builtin_env},
		{"setenv", builtin_setenv},
		{"unsetenv", builtin_unsetenv},
		{"help", builtin_help},
		{"unset", builtin_unset},
		{"export", builtin_export},
		{"read", builtin_read},
		{"jobs", builtin_jobs},
		{"fg", builtin_fg},
		{"bg", builtin_bg},
		{NULL, builtin_exit}
	};

	return ((void *)f);
}

int					boot_builtin(t_list *environ, char **cmds)
{
	int			i;
	t_builtin	*builtins;

	i = 0;
	builtins = builtins_get();
	while (builtins[i].name != NULL)
	{
		if (ft_strcmp(builtins[i].name, cmds[0]) == 0)
			return (builtins[i].func(environ, cmds));
		i++;
	}
	return (0);
}

int					is_builtin(char **cmds)
{
	int			i;
	t_builtin	*builtins;

	i = 0;
	builtins = builtins_get();
	while (builtins[i].name != NULL)
	{
		if (ft_strcmp(builtins[i].name, cmds[0]) == 0)
			return (1);
		i++;
	}
	return (0);
}
