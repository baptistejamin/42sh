/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helpers_cd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 18:13:52 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/12 16:21:20 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int		builtin_cd_error(int type, char *path)
{
	ft_putstr_fd("cd: ", 2);
	if (type == 0)
		ft_putstr_fd("An error occured\n", 2);
	else if (type == 1)
		ft_putstr_fd("too many arguments\n", 2);
	else if (type == 2)
		ft_putstr_fd("string not in pwd\n", 2);
	else if (type == 3)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (type == 4)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Not a directory\n", 2);
	}
	else if (type == 5)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	return (1);
}

char	*builtin_cd_assert_home(t_list *environ)
{
	int		fd;
	char	*logname;
	char	*line;

	logname = env_get(environ, "LOGNAME");
	if (*env_get(environ, "HOME") == '\0')
	{
		fd = open("/etc/passwd", O_RDONLY);
		if (fd < 0 || !*logname)
			return (NULL);
		while (get_next_line(fd, &line))
		{
			if (ft_strncmp(logname, line, ft_strlen(logname)) == 0)
				return (ft_strrchr(line, ':') + 1);
		}
		close(fd);
		return (NULL);
	}
	return (env_get(environ, "HOME"));
}

char	*builtin_cd_assert_multiple_args(char **cmds,
												t_generic_options *options)
{
	char	cdpath[PATH_MAX];
	char	directory[PATH_MAX];

	if (cmds[options->start] && cmds[options->start + 1]
		&& cmds[options->start + 2])
	{
		builtin_cd_error(1, "");
		return (NULL);
	}
	getcwd(cdpath, PATH_MAX);
	if (!ft_strstr(cdpath, cmds[options->start]))
		builtin_cd_error(2, "");
	else
	{
		directory[0] = 0;
		ft_strncat(directory, cdpath, ft_strlen(cdpath) -
			ft_strlen(ft_strstr(cdpath, cmds[options->start])) - 1);
		ft_strcat(directory, "/");
		ft_strcat(directory, cmds[options->start + 1]);
		ft_strcat(directory, ft_strstr(cdpath, cmds[options->start]) +
			ft_strlen(cmds[options->start]));
		return (ft_strdup(directory));
	}
	return (NULL);
}

void	builtin_cd_update_path(t_list **environ,
											char *old_path, char *path)
{
	t_sh	*sh;

	UNUSED(environ);
	sh = t_sh_recover();
	env_set(&sh->env_list, "OLDPWD", old_path);
	env_set(&sh->env_list, "PWD", path);
}

int		builtin_cd_change_directory(t_list **environ,
												char *curpath, int is_physical)
{
	t_sh 		*sh;
	t_stat		stat_;
	char		old_path[PATH_MAX];
	char		new_path[PATH_MAX];

	sh = t_sh_recover();
	getcwd(old_path, 256);
	if (stat(curpath, &stat_) == -1)
		return (builtin_cd_error(3, curpath));
	if (!S_ISDIR(stat_.st_mode))
		return (builtin_cd_error(4, curpath));
	if (chdir(curpath) != 0)
		return (builtin_cd_error(5, curpath));
	getcwd(new_path, 256);
	if (is_physical)
		builtin_cd_update_path(environ, ft_strdup(old_path),
		curpath);
	else
		builtin_cd_update_path(environ, ft_strdup(old_path),
		ft_strdup(new_path));
	return (0);
}
