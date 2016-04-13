/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 23:49:18 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/13 20:10:45 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <stdlib.h>
# include <libft.h>
# include <lexer.h>
# include <termios.h>
# include <fcntl.h>

typedef enum			e_job_linker
{
	LINK_THEN,
	LINK_AND,
	LINK_OR,
	LINK_TO_BACKGROUND
}						t_job_linker;

typedef struct			s_io_channel
{
	int					fd;
	char				to_close;
}						t_io_channel;

typedef struct			s_process
{
	char				**argv;
	pid_t				pid;
	int					status;
	char				completed;
	char				stopped;
	t_io_channel		stdio[3];
}						t_process;

typedef struct			s_job
{
	char				*command;
	t_list				*process_list;
	pid_t				pgid;
	char				notified;
	struct termios		tmodes;
	t_job_linker		linker;
}						t_job;


t_list					*token_list_to_job_list(t_list *token_list);
t_list					*parse_job(t_list *token_split);
t_list					*parse_process(t_token *t);

int 					parser_assert_linker(t_token *t);
int						parser_assert_pipe(t_token *t);
int						parser_assert_cmd(t_token *t);

char					**parse_cmd_argv(t_process *p, char *cmd);

void					parse_io_channel(t_process *p, char *redir, char *target);
t_io_channel			get_default_stdin(void);
t_io_channel			get_default_stdout(void);
t_io_channel			get_default_stderr(void);

#endif