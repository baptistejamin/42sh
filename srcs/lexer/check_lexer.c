/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 14:06:48 by nathan            #+#    #+#             */
/*   Updated: 2016/04/29 18:13:09 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

static void		check_lexer_error(char *token)
{
	ft_putstr("42sh: syntax error near unexpected token `");
	ft_putstr(token);
	ft_putendl("`");
}

static int		check_lexer_single_bg(t_list * t_list)
{
	t_token	*t;

	if (!t_list)
		return (1);
	t = t_list->content;
	if (!t)
		return (1);
	if (t->type == TO_BACKGROUND)
	{
		check_lexer_error("&");
		return (1);
	}
	return (0);
}

int				check_lexer(t_list *token_list)
{
	t_token	*t;
	t_token	*t_next;

	t = NULL;
	if (!token_list || check_lexer_single_bg(token_list))
		return (1);
	while (token_list->next)
	{
		t = token_list->content;
		t_next = token_list->next->content;
		if (t->type == PIPE && t_next->type != CMD)
		{
			check_lexer_error("|");
			return (1);
		}
		token_list = token_list->next;
	}
	t = token_list->content;
	if (!t || (t && (t->type == PIPE || t->type == OR || t->type == AND)))
	{
		check_lexer_error("\\n");
		return (1);
	}
	return (0);
}
