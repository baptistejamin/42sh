/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helpers_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:13:52 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/18 16:45:18 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

static int	file_cmd(t_list *environ, char **cmds)
{
	struct stat stat_;

	if (lstat(cmds[0], &stat_) == -1)
	{
		errors_no_file_directory(cmds[0]);
		return (-1);
	}
	if (S_ISDIR(stat_.st_mode))
	{
		errors_is_directory(cmds[0]);
		return (-1);
	}
	if (access(cmds[0], X_OK) == 0)
		return (env_launch_cmd(environ, cmds[0], cmds));
	errors_no_file_directory(cmds[0]);
	return (-1);
}

int			env_launch_cmd(t_list *environ, char *cmd, char **args)
{
	int					pid;

	reset_major_signals();
	if ((pid = fork()) == 0)
		execve(cmd, args, env_from_list(environ));
	else
		waitpid(pid, 0, 0);
	ignore_major_signals();
	return (0);
}

int			env_boot_cmd(t_sh *sh, t_list *environ, char **cmds)
{
	char	**path;
	char	*tmp;
	int		i;

	path = ft_strsplit(env_get(sh->env_list, "PATH"), ':');
	i = 0;
	if (ft_strchr(cmds[0], '/') != NULL)
		return (file_cmd(environ, cmds));
	while (path && path[i])
	{
		tmp = ft_strfjoin(ft_strjoin(path[i], "/"), cmds[0]);
		if (access(tmp, X_OK) == 0)
		{
			ft_free_tab(path);
			return (env_launch_cmd(environ, tmp, cmds));
		}
		free(tmp);
		tmp = NULL;
		i++;
	}
	errors_not_found(cmds[0]);
	if (path)
		ft_free_tab(path);
	return (-1);
}

int			env_boot(t_list *environ, char **cmds)
{
	t_sh *sh;

	sh = t_sh_recover();
	if (cmds[0] && is_builtin(cmds))
		return (boot_builtin(environ, cmds));
	else if (cmds[0])
		return (env_boot_cmd(sh, environ, cmds));
	return (-1);
}
