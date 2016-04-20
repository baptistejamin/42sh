/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 12:05:45 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/20 19:52:58 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>

int		is_job_success(t_job *j)
{
	t_list		*process_list;
	t_process	*p;

	if (!job_is_completed(j))
		return (1);
	process_list = j->process_list;
	while (process_list)
	{
		p = process_list->content;
		if (p->status != 0)
			return (0);
		process_list = process_list->next;
	}
	return (1);
}

int		get_job_exit_code(t_job *j)
{
	t_list		*process_list;
	t_process	*p;

	process_list =  j->process_list;
	while (process_list)
	{
		p =	process_list->content;
		if (p->completed && p->status != 0)
			return (p->status);
		process_list = process_list->next;
	}
	return (0);
}
