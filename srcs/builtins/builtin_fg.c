/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/19 20:12:58 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <executor.h>

int		builtin_fg_default(void)
{
	t_job	*job;

	job = find_job_by_index(1);
	if (!job)
	{
		ft_putendl_fd("fg: no current job", 2);
		return (1);
	}
	put_job_in_foreground(job, 1);
	return (0);
}

int		builtin_fg(t_list *environ, char **cmds)
{
	int		i;
	t_sh	*sh;
	t_job	*job;

	i = 1;
	sh = t_sh_recover();
	UNUSED(environ);
	while (cmds[i])
	{
		job = find_job_by_index(ft_atoi(cmds[i]));
		if (job)
			put_job_in_foreground(job, 1);
		else
		{
			ft_putstr_fd("fg: job not found: ", 2);
			ft_putendl_fd(cmds[i], 2);
			return (1);
		}
		i++;
	}
	if (cmds[1] == NULL)
		return (builtin_fg_default());
	else
		return (0);
}
