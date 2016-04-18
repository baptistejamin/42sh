/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 18:24:02 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/18 18:13:21 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <executor.h>
#include <builtins.h>

void		launch_process_builtin(t_process *p)
{
	t_sh	*shell;

	shell = t_sh_recover();
	p->status = boot_builtin(shell->env_list, p->argv);
	p->completed = 1;
}

static void	get_new_stdio(t_process *p, t_io_channel *s)
{
	if (s[0].fd != 0)
	{
		dup2(p->stdio[0].fd, 0);
		close(p->stdio[0].fd);
	}
	if (s[1].fd != 1)
	{
		dup2(p->stdio[1].fd, 1);
		close(p->stdio[1].fd);
	}
	if (s[2].fd != 2)
	{
		dup2(p->stdio[2].fd, 2);
		close(p->stdio[2].fd);
	}
}

void		launch_process(t_process *p, pid_t pgid, int foreground)
{
	char	**env;
	t_sh	*shell;
	pid_t	pid;

	if (!p)
		exit(1);
	pid = getpid();
	if (pgid == 0)
		pgid = pid;
	setpgid(pid, pgid);
	if (foreground)
		tcsetpgrp(0, pgid);
	shell = t_sh_recover();
	env = env_from_list(shell->env_list);
	reset_major_signals();
	get_new_stdio(p, p->stdio);
	execve(p->argv[0], p->argv, env);
	ft_putstr("42sh: command not found: ");
	ft_putendl(p->argv[0]);
	exit(1);
}

int		update_process_status(t_job *j, pid_t pid, int status)
{
	t_list	*process;

	process = j->process_list;
	while (process)
	{
		if (((t_process *)process->content)->pid == pid)
		{
			if (WIFEXITED(status))
			{
				((t_process *)process->content)->status = WEXITSTATUS(status);
				((t_process *)process->content)->completed = 1;
			}
			if (WIFSIGNALED(status))
			{
				((t_process *)process->content)->status = WTERMSIG(status);
				((t_process *)process->content)->completed = 1;
			}
			if (WIFSTOPPED(status))
				((t_process *)process->content)->stopped = 1;
			return (0);
		}
		process = process->next;
	}
	return (0);
}