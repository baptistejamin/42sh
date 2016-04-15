/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 18:24:02 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/15 20:02:08 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <executor.h>
#include <stdio.h>
void		launch_process(t_process *p, int foreground)
{
	char	**env;
	t_sh	*shell;

	if (!p)
		exit(1);
	shell = t_sh_recover();
	env = env_from_list(shell->env_list);
	if (foreground)
		tcsetpgrp(0, getpgrp());
	reset_major_signals();
	dup2(p->stdio[0].fd, 0);
	dup2(p->stdio[1].fd, 1);
	dup2(p->stdio[2].fd, 2);
	printf("executing command %s\n", p->argv[0]);
	execve(p->argv[0], p->argv, env);
	//perror ?
	exit(1);
}

void		update_process_status(t_job *j, pid_t pid, int status)
{
	t_list	*process;

	printf("updating status of process %d\n", pid);
	process = j->process_list;
	while (process)
	{
		if (((t_process *)process->content)->pid == pid)
		{
			((t_process *)process->content)->status = status;
			((t_process *)process->content)->completed = 1;
			return ;
		}
		process = process->next;
	}
}