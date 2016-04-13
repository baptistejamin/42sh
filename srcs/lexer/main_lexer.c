/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 15:52:31 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/13 22:00:06 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

t_token_matcher		g_token_matcher[] = {
	{OR, &is_token_or},
	{AND, &is_token_and},
	{SEMI_COLON, &is_token_semi_colon},
	{TO_BACKGROUND, &is_token_to_background},
	{PIPE, &is_token_pipe},
	{QUOTE_BACK, &is_token_quote_back},
	{PARENT_OPEN, &is_token_parent_open},
	{PARENT_CLOSE, &is_token_parent_close},
	{TOKEN_TYPE_END_LIST, NULL}
};

static int		read_token(t_list **token_list, char *str)
{
	int		i;
	int		length;

	i = 0;
	while (g_token_matcher[i].type != TOKEN_TYPE_END_LIST)
	{
		length = g_token_matcher[i].match_function(str);
		if (length != 0)
		{
			ft_lstadd_back(token_list,
				new_token(g_token_matcher[i].type, NULL));
			return (length);
		}
		i++;
	}
	return (0);
}

static void		cmd_to_token(t_list **token_list, char *str, int length)
{
	char	*word;
	int		i;

	i = 0;
	if (length <= 0)
		return ;
	while (ft_isspace(str[i]))
		i++;
	word = ft_strsub(str, i, length);
	ft_lstadd_back(token_list, new_token(CMD, word));
}

t_list			*input_to_token_list(char *input)
{
	int		i;
	t_list	*token_list;

	i = 0;
	token_list = NULL;
	while (*input)
	{
		while (ft_isspace(*input))
			input++;
		while (input[i] == '\\' && input[i + 1])
			i += 2;
		if (input[i] == '\'' || input[i] == '"')
			i += lexer_skip_quotes(input + i);
		if (is_token(input + i) || !input[i])
		{
			cmd_to_token(&token_list, input, i);
			while (ft_isspace(input[i]))
				i++;
			i += read_token(&token_list, input + i);
			input += i;
			i = 0;
		}
		else
			i++;
	}
	return (token_list);
}
