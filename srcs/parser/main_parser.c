/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 23:49:07 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/13 04:37:55 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <stdio.h>
t_list					*token_list_to_job_list(t_list *token_list)
{
	t_list		*job_list;
	t_list		*token_split;
	t_list		*token_split_end;

	job_list = NULL;
	while (token_list)
	{
		token_split = token_list;
		token_split_end = token_list;
		while (token_split_end->next &&
			!parser_assert_linker(token_split_end->content))
			token_split_end = token_split_end->next;
		token_list = token_split_end->next;
		token_split_end->next = NULL;
		ft_lstadd_back(&job_list, parse_job(token_split));
		ft_lstdel(&token_split, &del_token);
	}
	return (job_list);
}

static t_job_linker		get_token_linker(t_list *t)
{
	t_token *tt;

	if (!t || (t && !t->content))
		return (LINK_THEN);
	tt = (t_token *)t->content;
	if (tt->type == AND)
		return (LINK_AND);
	if (tt->type == OR)
		return (LINK_OR);
	if (tt->type == TO_BACKGROUND)
		return (LINK_TO_BACKGROUND);
	return (LINK_THEN);
}

t_list					*parse_job(t_list *token_split)
{
	t_job		job;

	if (!token_split)
		return (NULL);
	ft_memset(&job, 0, sizeof(t_job));
	while (token_split->next && parser_assert_pipe(token_split->next->content))
	{
		if (parser_assert_cmd(token_split->content))
			ft_lstadd_back(&(job.process_list),
				parse_process(token_split->content));
		token_split = token_split->next->next;
	}
	if (token_split && parser_assert_cmd(token_split->content))
	{
		ft_lstadd_back(&(job.process_list),
			parse_process(token_split->content));
		token_split = token_split->next;
	}
	job.linker = get_token_linker(token_split);
	return (ft_lstnew(&job, sizeof(t_job)));
}

t_list					*parse_process(t_token *t)
{
	t_process		p;

	if (!t || (t && t->type != CMD))
		return (NULL);
	ft_memset(&p, 0, sizeof(t_process));
	p.stdio[0] = get_default_stdin();
	p.stdio[1] = get_default_stdout();
	p.stdio[2] = get_default_stderr();
	p.argv = ft_strsplit(t->content, ' ');
	return (ft_lstnew(&p, sizeof(t_process))); //Leak memory from above strsplit
}