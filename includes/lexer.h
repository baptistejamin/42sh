/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 15:22:50 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/12 16:35:50 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <libft.h>

typedef enum		e_token_type
{
	WORD,
	OR,
	AND,
	SEMI_COLON,
	TO_BACKGROUND,
	PIPE,
	QUOTE_SIMPLE,
	QUOTE_DOUBLE,
	QUOTE_BACK,
	REDIR_APPEND_OUTPUT,
	REDIR_TRUNCATE_OUTPUT,
	REDIR_HEREDOC,
	REDIR_GET_INPUT,
	PARENT_OPEN,
	PARENT_CLOSE,
	TOKEN_TYPE_END_LIST
}					t_token_type;

typedef struct		s_token_matcher
{
	t_token_type	type;
	int				(*match_function)(char *)

}					t_token_matcher;

typedef struct		s_token
{
	t_token_type	type;
	void			*content;
}					t_token;
/*
** Main lexer
*/
t_list				*input_to_token_list(char *input);
/*
** Token manipulation
*/
t_list				*new_token(t_token_type type, void *content);
void				del_token(void *token_void, size_t size_content);



/*
** Token matching functions
*/
int					is_token_and(char *line);
int					is_token_or(char *line);
int					is_token_semi_colon(char *line);
int					is_token_to_background(char *line);
int					is_token_pipe(char *line);
int					is_token_quote_simple(char *line);
int					is_token_quote_double(char *line);
int					is_token_quote_back(char *line);
int					is_token_redir_append_output(char *line);
int					is_token_redir_truncate_output(char *line);
int					is_token_redir_heredoc(char *line);
int					is_token_redir_get_input(char *line);
int					is_token_parent_open(char *line);
int					is_token_parent_close(char *line);


#endif
