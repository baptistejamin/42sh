/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token_quotes_parent.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 15:43:35 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/12 15:44:55 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

int		is_token_quote_back(char *line)
{
	if (*line == '`')
		return (1);
	return (0);
}

int		is_token_quote_simple(char *line)
{
	if (*line == '\'')
		return (1);
	return (0);
}

int		is_token_quote_double(char *line)
{
	if (*line == '"')
		return (1);
	return (0);
}

int		is_token_parent_close(char *line)
{
	if (*line == ')')
		return (1);
	return (0);
}

int		is_token_parent_open(char *line)
{
	if (*line == '(')
		return (1);
	return (0);
}
