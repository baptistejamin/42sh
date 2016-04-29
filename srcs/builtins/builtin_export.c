/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/29 16:20:40 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static int	builtin_export_set_vars_error(void)
{
	ft_putendl_fd("Your variables must be alphanumeric", 2);
	return (-1);
}

static int	builtin_export_set_vars(t_generic_options *options, char **cmds)
{
	int		i;
	char	*var;
	char	*value;
	t_sh	*sh;

	sh = t_sh_recover();
	i = options->start;
	while (cmds[i])
	{
		if (ft_strchr(cmds[i], '='))
		{
			var = ft_strnew(ft_strlen(cmds[i]) -
			ft_strlen(ft_strchr(cmds[i], '=') + 1));
			ft_strncpy(var, cmds[i], ft_strlen(cmds[i]) -
			ft_strlen(ft_strchr(cmds[i], '=')));
			value = ft_strdup(ft_strchr(cmds[i], '=') + 1);
			if (ft_strchr(value, '=') || !ft_str_alnum(var))
				return (builtin_export_set_vars_error());
			env_set(&sh->vars_list, var, value);
		}
		else
			return (i);
		i++;
	}
	return (i);
}

int			builtin_export(t_list *environ, char **cmds)
{
	t_generic_options	options;
	t_sh				*sh;

	UNUSED(environ);
	sh = t_sh_recover();
	options = builtin_options_parser(cmds, "p");
	if (options.error)
	{
		ft_putstr_fd("export: illegal option -- ", 2);
		ft_putchar_fd(options.error_char, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	builtin_export_set_vars(&options, cmds);
	if (ft_is_in(options.options, 'p'))
		env_show(sh->vars_list);
	return (0);
}
