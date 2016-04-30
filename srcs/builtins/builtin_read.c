/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/30 16:34:09 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static int		builtin_read_r(char **cmds, int start)
{
	int		i;
	char	*line;
	t_sh	*sh;

	i = start;
	sh = t_sh_recover();
	while (get_next_line(0, &line) && cmds[i])
	{
		env_set(&sh->vars_list, cmds[i], line);
		i++;
		if (!cmds[i])
			return (0);
	}
	return (0);
}

static int		builtin_read_generic(char **cmds, int start)
{
	int		i;
	char	*line;
	t_sh	*sh;
	char	*str;
	int		should_repeat;

	i = start;
	sh = t_sh_recover();
	str = ft_strnew(1);
	should_repeat = 1;
	while (should_repeat && get_next_line(0, &line))
	{
		if (line && ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\\')
		{
			line[ft_strlen(line) - 1] = 0;
			should_repeat = 1;
		}
		else
			should_repeat = 0;
		str = ft_strfjoin(str, line);
	}
	env_set(&sh->vars_list, cmds[i], str);
	return (0);
}

int				builtin_read(t_list *environ, char **cmds)
{
	t_sh				*sh;
	t_generic_options	options;

	sh = t_sh_recover();
	UNUSED(environ);
	options = builtin_options_parser(cmds, "r");
	if (options.error)
	{
		ft_putstr_fd("bad option: -", 2);
		ft_putchar_fd(options.error_char, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	if (!ft_is_in(options.options, 'r'))
		return (builtin_read_generic(cmds, options.start));
	else
		return (builtin_read_r(cmds, options.start));
}
