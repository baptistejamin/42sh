/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 12:05:45 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/18 12:09:36 by ngrasset         ###   ########.fr       */
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
