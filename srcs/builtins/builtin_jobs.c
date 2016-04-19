/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 19:05:26 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/19 20:13:11 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>
#include <shell.h>

int		builtin_jobs(t_list *environ, char **av)
{
	t_sh	*shell;
	t_list	*job_list;
	int		i;

	(void)environ;
	(void)av;
	shell = t_sh_recover();
	job_list = shell->jobs;
	i = 1;
	while (job_list)
	{
		if (!((t_job *)job_list->content)->notified)
			put_job_info(job_list->content, i);
		i++;
		job_list = job_list->next;
	}
	return (0);
}
