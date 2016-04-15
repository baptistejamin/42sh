/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 18:48:42 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/16 00:20:31 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <executor.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/errno.h>
void	launch_job(t_job *j, int foreground)
{
	t_list		*process_list;
	t_process 	*process;
	int			infile;
	int			outfile;
	int			pipe_fd[2];
	pid_t		child_pid;

	infile = 0;
	process_list = j->process_list;
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
		if ((child_pid = fork()) == 0) //Handle fork errors?
		{
			process->stdio[0].fd = infile;
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
		put_job_in_foreground(j);
	else
		put_job_in_background(j);
}

void	put_job_in_background(t_job *j)
{
	(void)j;
	//Need to log new background task
}

void	put_job_in_foreground(t_job *j)
{
	t_sh	*shell;

	shell = t_sh_recover();
	tcsetpgrp(0, j->pgid);
	wait_for_job(j);
	tcsetpgrp(0, shell->pgid);
	//Maybe restore default termcaps ?
}

void	wait_for_job(t_job *j)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = 0;
	while (!job_is_completed(j))
	{
		pid = waitpid(- j->pgid, &status, WUNTRACED);
		update_process_status(j, pid, status);
		if (pid == -1)
		{
			printf("pid == -1\n");
			break ;		//Hacky, this should not happend all the time :(
		}
		status = 0;
	}
}

int		job_is_completed(t_job *j)
{
	t_list	*process;

	process = j->process_list;
	while (process)
	{
		if (!((t_process *)(process->content))->completed)
			return (0);
		process = process->next;
	}
	return (1);
}