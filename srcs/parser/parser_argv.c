/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 19:21:33 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/13 19:48:25 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <stdio.h>
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

char			**parse_cmd_argv(t_process *p, char *cmd)
{
	char	**argv;
	char	**split;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(argv = malloc(sizeof(char *) * count_args(clear_str_space(cmd)))) ||
		!(split = ft_strsplit(cmd, ' ')))
		return (NULL);
	while (split[j])
	{
		if (is_token_redir(split[j]) && split[j + 1])
		{
			parse_io_channel(p, split[j], split[j + 1]);
			j += 2;
		}
		else
			argv[i++] = ft_strdup(split[j++]);
	}
	argv[i] = NULL;
	//ft_delstrtab(split);
	return (argv);
}