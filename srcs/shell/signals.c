/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 18:32:25 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/19 20:26:20 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <shell.h>

static void		signal_reprompt(int i)
{
	UNUSED(i);
	prompt_display(0);
	prompt_add_new();
	ft_putstr("\n");
	prompt_display(1);
}

static void		signal_resize(int i)
{
	UNUSED(i);
	prompt_update_window();
	prompt_display(1);
}

void			ignore_major_signals(void)
{
	signal(SIGWINCH, signal_resize);
	signal(SIGINT, signal_reprompt);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
}

void			reset_major_signals(void)
{
	signal(SIGWINCH, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
}
