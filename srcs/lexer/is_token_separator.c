/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token_separator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 15:48:18 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/12 15:51:10 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

int		is_token_and(char *line)
{
	if (*line == '&' && *(line + 1) == '&')
		return (2);
	return (0);
}

int		is_token_or(char *line)
{
	if (*line == '|' && *(line + 1) == '|')
		return (2);
	return (0);
}

int		is_token_semi_colon(char *line)
{
	if (*line == ';')
		return (1);
	return (0);
}

int		is_token_to_background(char *line)
{
	if (*line == '&')
		return (1);
	return (0);
}

int		is_token_pipe(char *line)
{
	if (*line == '|')
		return (1);
	return (0);
}
