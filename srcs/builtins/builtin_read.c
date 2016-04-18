/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/18 20:09:29 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int		builtin_read(t_list *environ, char **cmds)
{
	int		i;
	char	*line;
	t_sh	*sh;

	i = 1;
	sh = t_sh_recover();
	UNUSED(environ);
	while (get_next_line(0, &line) && cmds[i])
	{
		env_set(&sh->vars_list, cmds[i], line);
		i++;
		if (!cmds[i])
			return (0);
	}
	return (0);
}
