/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_io_channel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 04:10:04 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/13 21:46:20 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

static int			get_redir_channel(char *redir)
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
//DOESNT WORK, DONT HANDLE WHERE REDIRECTION SYMBOL '>' AND TARGET ARE
//NOT SEPERATED BY A SPACE (LIKE ls>foo)
void				parse_io_channel(t_process *p, char *redir, char *target)
{
	int		fd;
	int		from;

	if (is_token_redir_append_output(redir))
	{
		if ((fd = open(target, O_CREAT | O_WRONLY | O_APPEND, 0666)) == -1)
			fd = 1;
		if ((from = get_redir_channel(redir)) == 0)
			from = 1;
		p->stdio[from].fd = fd;
		p->stdio[from].to_close = 1;
	}
	if (is_token_redir_truncate_output(redir))
	{
		if ((fd = open(target, O_CREAT | O_WRONLY | O_TRUNC, 0666)) == -1)
			fd = 1;
		if ((from = get_redir_channel(redir)) == 0)
			from = 1;
		p->stdio[from].fd = fd;
		p->stdio[from].to_close = 1;
	}
	if (is_token_redir_heredoc(redir))
		p->stdio[0].fd = 8; //TODO
	if (is_token_redir_get_input(redir))
		p->stdio[0].fd = 9; //TODO
}

t_io_channel		get_default_stdin(void)
{
	t_io_channel	c;

	c.fd = 0;
	c.to_close = 0;
	return (c);
}

t_io_channel		get_default_stdout(void)
{
	t_io_channel	c;

	c.fd = 1;
	c.to_close = 0;
	return (c);
}

t_io_channel		get_default_stderr(void)
{
	t_io_channel	c;

	c.fd = 2;
	c.to_close = 0;
	return (c);
}