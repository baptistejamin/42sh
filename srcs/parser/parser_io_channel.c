/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_io_channel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 04:10:04 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/13 04:39:53 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

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