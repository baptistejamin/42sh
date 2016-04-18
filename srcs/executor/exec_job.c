/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 18:48:42 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/18 21:59:36 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <executor.h>
#include <unistd.h>


void			exec_job_list(t_list *job_list)
{
	t_job	*j;

	while (job_list) {
		j = job_list->content;
		prepare_job(j);
		if (j->linker != LINK_TO_BACKGROUND)
			launch_job(job_list->content, 1);
		else
			launch_job(job_list->content, 0);
		if (!job_is_completed(j) && job_is_stopped(j) &&
			j->linker != LINK_TO_BACKGROUND)
			put_job_in_background(j, 0);
		else if (is_job_success(j) && j->linker == LINK_OR)
		{
			while (job_list->next && ((t_job *)job_list->content)->linker == LINK_OR)
				job_list = job_list->next;
		}
		else if (!is_job_success(j) && j->linker == LINK_AND)
		{
			while (job_list->next && ((t_job *)job_list->content)->linker == LINK_AND)
				job_list = job_list->next;
		}
		job_list = job_list->next;	
	}
}

void			launch_job(t_job *j, int foreground)
{
	t_list		*process_list;
	t_process 	*process;
	int			infile;
	int			outfile;
	int			pipe_fd[2];
	pid_t		child_pid;

	process_list = j->process_list;
	infile = 0;
	child_pid = 0;
	while (process_list)
	{
		process = process_list->content;
		if (process_list->next)
		{
			pipe(pipe_fd); //Handle pipe errors?
			outfile = pipe_fd[1];
		}
		else
			outfile = 1;
		if (is_builtin(process->argv))
		{
			process->stdio[0].fd = infile;
			process->stdio[1].fd = outfile;
			launch_process_builtin(process);
		}
		else if ((child_pid = fork()) == 0) //Handle fork errors?
		{
			if (infile != 0)
				process->stdio[0].fd = infile;
			if (outfile != 1)
				process->stdio[1].fd = outfile;
			launch_process(process, j->pgid, foreground);
		}
		process->pid = child_pid;
		if (!j->pgid)
			j->pgid = child_pid;
		setpgid(child_pid, j->pgid);
		process_list = process_list->next;

		if (infile != 0)
			close (infile);
		if (outfile != 1)
			close (outfile);
		infile = pipe_fd[0];
	}
	if (foreground)
		put_job_in_foreground(j, 0);
	else
		put_job_in_background(j, 0);
}
