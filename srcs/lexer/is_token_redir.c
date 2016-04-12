/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 15:43:57 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/12 15:47:10 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

int		is_token_redir_append_output(char *line)
{
	int		i;

	i = 0;
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] == '>' && line[i + 1] == '>')
		return (i + 2);
	return (0);
}

int		is_token_redir_truncate_output(char *line)
{
	int		i;

	i = 0;
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] == '>')
		return (i + 1);
	return (0);
}

int		is_token_redir_heredoc(char *line)
{
	int		i;

	i = 0;
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] == '<' && line[i + 1] == '<')
		return (i + 2);
	return (0);
}

int		is_token_redir_get_input(char *line)
{
	int		i;

	i = 0;
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] == '<')
		return (i + 1);
	return (0);
}
