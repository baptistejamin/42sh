/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_io_channel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 04:10:04 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/14 18:18:43 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static int 		parse_truncate_redir(t_process *p, int channel, char *target)
{
	int		fd;

	if ((fd = open(target, O_CREAT | O_WRONLY | O_TRUNC, 0666)) == -1)
		fd = 1;
	p->stdio[channel].fd = fd;
	p->stdio[channel].to_close = 1;
	return (0);
}

static int 		parse_append_redir(t_process *p, int channel, char *target)
{
	int		fd;

	if ((fd = open(target, O_CREAT | O_WRONLY | O_APPEND, 0666)) == -1)
		fd = 1;
	p->stdio[channel].fd = fd;
	p->stdio[channel].to_close = 1;
	return (0);
}

static int	parse_heredoc_redir(t_process *p, int channel, char *target)
{
	(void)p;
	(void)channel;
	(void)target;
	//p->stdio[0].fd = -1;
	return (0);
}

static int	parse_input_redir(t_process *p, int channel, char *target)
{
	(void)p;
	(void)channel;
	(void)target;
	//p->stdio[0].fd = -2;
	return (0);
}

int			parse_io_channel(t_process *p, char **split)
{
	
	if (is_aggregate_fd(*split))
		return (aggreagate_fd(p, *split));
	if (is_token_redir_append_output(*split))
		return (count_target_length(p, split, '>', &parse_append_redir));
	if (is_token_redir_truncate_output(*split))
		return (count_target_length(p, split, '>', &parse_truncate_redir));
	if (is_token_redir_heredoc(*split))
		return (count_target_length(p, split, '<', &parse_heredoc_redir));
	if (is_token_redir_get_input(*split))
		return (count_target_length(p, split, '<', &parse_input_redir));
	return (1);
}
