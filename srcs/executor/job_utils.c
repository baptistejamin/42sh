/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 17:38:10 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/18 17:54:44 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>
#include <shell.h>

t_job		*find_job_by_gpid(t_list *job_list, pid_t pgid)
{
	t_job	*j;

	while (job_list)
	{
		j = job_list->content;
		if (j->pgid == pgid)
			return (j);
		job_list = job_list->next;
	}
	return (NULL);
}

t_job		*find_job_by_pid(t_list *job_list, pid_t pid)
{
	t_job		*j;
	t_list		*process_list;
	t_process	*p;

	while (job_list)
	{
		j = job_list->content;
		process_list = j->process_list;
		while (process_list)
		{
			p = process_list->content;
			if (p->pid == pid)
				return (j);
			process_list = process_list->next;
		}
		job_list = job_list->next;
	}
	return (NULL);
}

int			find_job_index(pid_t pgid)
{
	t_sh	*shell;
	t_list	*job_list;
	int		i;

	shell = t_sh_recover();
	job_list = shell->jobs;
	i = 1;
	while (job_list)
	{
		if (((t_job *)job_list->content)->pgid == pgid)
			return (i);
		job_list = job_list->next;
		i++;
	}
	return (0);
}