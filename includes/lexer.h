/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 20:06:40 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/11 20:09:38 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

t_list	*new_token_list(char *input)
{
	t_lish *new_list;

	new_list = NULL;
	while(*input)
	{
		ft_lstadd(&new_list, lst_new(10, sizeof(t_token)));
		input++;
	}
}

#endif