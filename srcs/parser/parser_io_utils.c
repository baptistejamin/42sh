/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_io_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 18:14:42 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/14 18:16:38 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

int		get_redir_channel(char *redir)
{
	int		fd;

	if (!redir || (redir && !*redir))
		return (1);
	if (*redir == '>')
		return (1);
	if (*redir == '<')
		return (0);
	fd = ft_atoi(redir);
	if (fd > 2) //dont handle fd bigger than 2 for now
		return (1);
	return (fd);
}

int		count_target_length(t_process *p, char **split, char symbol,
			int (*parse_fn)(t_process *, int, char *))
{
	int		channel;

	channel = get_redir_channel(*split);
	if (*(ft_strrchr(*split, symbol) + 1))
	{
		parse_fn(p, channel, ft_strrchr(*split, symbol) + 1);
		return (1);
	}
	else
	{
		parse_fn(p, channel, *(split + 1));
		return (2);
	}

}

int		is_aggregate_fd(char *redir)
{
	int		i;

	i = 0;
	while (ft_isdigit(redir[i]))
		i++;
	while (redir[i] == '>' || redir[i] == '<')
		i++;
	if (redir[i] == '&')
		return (1);
	return (0);
}

int		aggreagate_fd(t_process *p, char *redir)
{
	int				channel;
	int				channel_target;
	int				i;

	channel = get_redir_channel(redir);
	i = 0;
	while (ft_isdigit(redir[i]))
		i++;
	while (redir[i] == '>' || redir[i] == '<')
		i++;
	i++;
	if (!ft_isdigit(redir[i]))
		channel_target = 1;
	else
		channel_target = ft_atoi(redir + i);
	if (channel_target > 2)
		channel_target = 1;
	p->stdio[channel_target] = p->stdio[channel];
	return (1);
}