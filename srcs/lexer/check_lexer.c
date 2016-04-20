/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 14:06:48 by nathan            #+#    #+#             */
/*   Updated: 2016/04/20 14:16:01 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

static void		check_lexer_error(char *token)
{
	ft_putstr("42sh: syntax error near unexpected token `");
	ft_putstr(token);
	ft_putendl("`");
}

int				check_lexer(t_list *token_list)
{
	t_token	*t;
	t_token	*t_next;

	t = NULL;
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