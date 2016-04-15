/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 19:21:33 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/15 17:49:24 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

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

	res = ft_strdup(arg);
	return (res); //need to escape quotes
}

char			**parse_cmd_argv(t_process *p, char *cmd)
{
	char	**argv;
	char	**split;
	char	**start_split;
	int		i;

	i = 0;
	if (!(argv = malloc(sizeof(char *) * count_args(clear_str_space(cmd)) + 1)) ||
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
