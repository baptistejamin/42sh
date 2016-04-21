/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/21 16:17:51 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int	builtin_echo(t_list *environ, char **cmds)
{
	t_sh				*sh;
	int					i;
	t_generic_options	options;

	UNUSED(environ);
	sh = t_sh_recover();
	options = builtin_options_parser(cmds, "n");
	i = options.start;
	while (cmds[i])
	{
		if (!ft_is_in(options.options, 'n'))
			ft_putendl(cmds[i]);
		else
		{
			if (i != options.start)
				ft_putstr(" ");
			ft_putstr(cmds[i]);
		}
		i++;
	}
	if (ft_is_in(options.options, 'n'))
		ft_putendl("");
	return (0);
}
