/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_notification.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 16:12:19 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/18 18:15:09 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <executor.h>
#include <shell.h>

void		put_job_info(t_job *j, int index)
{
	ft_putstr("[");
	ft_putnbr(index);
	ft_putstr("] ");
	ft_putnbr(j->pgid);
	if (job_is_completed(j))
		ft_putstr("\tdone\t");
	else if (job_is_stopped(j))
		ft_putstr("\tstopped\t");
	else
		ft_putstr("\trunning\t");
	if (j->command)
		ft_putendl(j->command);
	else
		ft_putendl("(unknown command)");
}

int			update_process_status_by_pid(t_list *process_list, pid_t pid, int status)
{
	t_process	*p;

	while (process_list)
	{
		p = process_list->content;
		if (p->pid == pid)
		{
			if (WIFEXITED(status))
			{
				p->status = WEXITSTATUS(status);
				p->completed = 1;
			}
			if (WIFSIGNALED(status))
			{
				p->status = WTERMSIG(status);
				p->completed = 1;
			}
			if (WIFSTOPPED(status))
				p->stopped = 1;
			return (1);
		}
		process_list = process_list->next;
	}
	return (0);
}

void		update_job_status_by_pid(t_list *job_list, pid_t pid, int status)
{
	t_job		*j;

	if (!job_list)
		return ;
	if (pid < 1)
		return ;
	while (job_list)
	{
		j = job_list->content;
		if (update_process_status_by_pid(j->process_list, pid, status))
			return ;
		job_list = job_list->next;
	}
}

static void	notify_terminated_jobs(t_list *job_list)
{
	t_job		*j;
	int			i;

	i = 0;
	while (job_list)
	{
		j = job_list->content;
		if (job_is_completed(j))
		{
			if (!j->notified)
				put_job_info(j, i + 1);
			j->notified = 1;
		}
		i++;
		job_list = job_list->next;
	}	
}

void		update_job_status(void)
{
	t_sh	*shell;
	pid_t	pid;
	int		status;

	shell = t_sh_recover();
	pid = 1;
	while (pid > 0)
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
		update_job_status_by_pid(shell->jobs, pid, status);
	}
	notify_terminated_jobs(shell->jobs);
}
