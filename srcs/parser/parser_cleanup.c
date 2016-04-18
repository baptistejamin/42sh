/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 16:46:30 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/18 17:51:19 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <unistd.h>

void	del_job(void *job_raw, size_t job_size)
{
	t_job	*j;

	if (job_size != sizeof(t_job) || !job_raw)
		return ;
	j = (t_job *)job_raw;
	if (j->command)
		free(j->command);
	if (j->process_list)
		ft_lstdel(&(j->process_list), del_process);
	free(j);
}

void	del_process(void *raw_process, size_t process_size)
{
	t_process	*p;

	if (process_size != sizeof(t_process) || !raw_process)
		return ;
	p = (t_process *)raw_process;
	if (p->argv)
		ft_free_tab(p->argv);
	if (p->stdio[0].to_close && p->stdio[0].fd > 2)
		close(p->stdio[0].fd);
	if (p->stdio[1].to_close && p->stdio[1].fd > 2)
		close(p->stdio[1].fd);
	if (p->stdio[2].to_close && p->stdio[2].fd > 2)
		close(p->stdio[2].fd);
	free(p);
}
