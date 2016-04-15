/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 18:48:42 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/15 20:03:05 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <executor.h>
#include <unistd.h>
#include <stdio.h>
void	launch_job(t_job *j, int foreground)
{
	t_list		*process_list;
	t_process 	*process;
	int			infile;
	int			pipe_fd[2];
	pid_t		child_pid;

	infile = 0;
	process_list = j->process_list;
	while (process_list)
	{
		process = process_list->content;
		if (infile != 0)
		{
			process->stdio[0].fd = infile;
			process->stdio[0].to_close = 1;
		}
		if (process_list->next)
		{
			pipe(pipe_fd); //Handle pipe errors?
			process->stdio[1].fd = pipe_fd[1];
			process->stdio[1].to_close = 1;
			infile = pipe_fd[0];
		}
		if ((child_pid = fork()) == 0) //Handle fork errors?
			launch_process(process, foreground);
		process->pid = child_pid;
		process_list = process_list->next;
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

	while (!job_is_completed(j))
	{
		pid = waitpid(0, &status, WUNTRACED);
		printf("waitpid returned pid %d\n", pid);
		update_process_status(j, pid, status);
		if (pid == -1)
			break ;		//Hacky, this should not happend all the time :(
	}
	printf("out of while loop\n");
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