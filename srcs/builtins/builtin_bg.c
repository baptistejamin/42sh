/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/18 22:46:45 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <executor.h>

int		builtin_bg_default()
{
	t_job	*job;

	job = find_job_by_index(1);
	if (!job)
	{
		ft_putendl_fd("fg: no current job", 2);
		return (1);
	}
	kill (- job->pgid, SIGCONT);
	put_job_info(job, find_job_index(job->pgid));
	return (0);
}

int		builtin_bg(t_list *environ, char **cmds)
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
		{
			kill (- job->pgid, SIGCONT);
			put_job_info(job, find_job_index(job->pgid));
		}
		else
		{
			ft_putstr_fd("fg: job not found: ", 2);
			ft_putendl_fd(cmds[i], 2);
			return (1);
		}
		i++;
	}
	if (cmds[1] == NULL)
		return (builtin_bg_default());
	else
		return (0);
}
