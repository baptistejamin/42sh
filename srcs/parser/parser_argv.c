/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 19:21:33 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/20 19:18:50 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <shell.h>

static size_t	count_args(const char *s)
{
	size_t	words;
	size_t	i;

	words = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 || ft_isspace(s[i - 1])) && !ft_isspace(s[i]))
			words++;
		i++;
	}
	return (words);
}

static char		*clear_str_space(char *s)
{
	char	*res;

	res = s;
	while (*s)
	{
		if (ft_isspace(*s))
			*s = ' ';
		s++;
	}
	return (res);
}

static char		*get_new_arg(char *arg)
{
	char		*res;
	t_sh		*shell;

	if (!arg)
		return (ft_strdup(""));
	shell = t_sh_recover();
	if (*arg == '$' && *(arg + 1))
		res = env_get(shell->env_list, arg + 1);
	else
		res = ft_strdup(arg);
	return (res);
}

char			*construct_job_command(t_list *process_list)
{
	char		*cmd;
	t_process	*p;
	int			i;

	cmd = NULL;
	while (process_list)
	{
		p = process_list->content;
		i = 0;
		while (p->argv && p->argv[i])
		{
			cmd = ft_strfjoin(cmd, p->argv[i++]);
			cmd = ft_strfjoin(cmd, " ");
		}
		if (process_list->next)
			cmd = ft_strfjoin(cmd, "| ");
		process_list = process_list->next;
	}
	return (cmd);
}

char			**parse_cmd_argv(t_process *p, char *cmd)
{
	char	**argv;
	char	**split;
	char	**start_split;
	int		i;

	i = 0;
	clear_str_space(cmd);
	if (!(argv = malloc(sizeof(char *) * count_args(cmd) + 1)) ||
		!(split = ft_strsplit(cmd, ' ')))
		return (NULL);
	start_split = split;
	while (*split)
	{
		if (is_token_redir(*split))
			split += parse_io_channel(p, split);
		else
		{
			argv[i++] = get_new_arg(*split);
			split++;
		}
	}
	argv[i] = NULL;
	ft_free_tab(start_split);
	return (argv);
}
