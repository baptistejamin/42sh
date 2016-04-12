/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes_controller.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 17:50:20 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/12 17:56:21 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

static int	lexer_skip_double_quote(char *input)
{
	int		length;

	length = 1;
	input++;
	while (*input && *input != '"')
	{
		if (*input == '\\' && *(input + 1))
		{
			length += 2;
			input += 2;
		}
		length++;
		input++;
	}
	if (*input)
		return (length + 1);
	else
		return (length);
}

static int	lexer_skip_single_quote(char *input)
{
	int		length;

	length = 1;
	input++;
	while (*input && *input != '\'')
	{
		length++;
		input++;
	}
	if (*input)
		return (length + 1);
	else
		return (length);
}

int			lexer_skip_quotes(char *input)
{
	if (*input == '\'')
		return (lexer_skip_single_quote(input));
	if (*input == '"')
		return (lexer_skip_double_quote(input));
	return (0);
}