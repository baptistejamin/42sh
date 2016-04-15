/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/15 17:52:50 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <prompt.h>
#include <parser.h>

t_sh			*t_sh_recover(void)
{
	static t_sh	sh;

	return (&sh);
}

static	void	prepare_env(void)
{
	char	*number;
	t_sh	*sh;

	sh = t_sh_recover();
	if (env_get(sh->env_list, "SHLVL"))
		number = ft_itoa(ft_atoi(env_get(sh->env_list, "SHLVL")) + 1);
	else
		number = ft_itoa(1);
	env_set(&sh->env_list, "SHLVL", number);
	if (number)
		free(number);
}

static int		shell(void)
{
	char	*input;
	int		is_last_cmd_empty;
	t_list	*token_list;
	t_list	*job_list;

	is_last_cmd_empty = 0;
	while (1)
	{
		prompt_init();
		if (!is_last_cmd_empty)
			prompt_add_new();
		prompt_display(1);
		input = prompt_input();
		if (input)
		{
			token_list = input_to_token_list(input);
			job_list = token_list_to_job_list(token_list);
			prompt_reset();
			free(input);
		}
	}
	return (0);
}

int				main(int argc, char **argv, char **environ)
{
	t_sh	*sh;

	UNUSED(argv);
	sh = t_sh_recover();
	sh->tty = open("/dev/tty", O_RDWR);
	if (argc > 1)
	{
		ft_putendl_fd("42sh cannot execute commands", 2);
		return (0);
	}
	sh->env_list = NULL;
	env_to_list(&sh->env_list, environ);
	prepare_env();
	return (shell());
}
