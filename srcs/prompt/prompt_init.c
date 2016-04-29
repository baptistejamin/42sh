/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/29 17:01:17 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <prompt.h>

void	prompt_error(void)
{
	ft_putendl("Termcaps. Cannot launch 42sh. Did you set env vars?");
	exit(1);
}

int		prompt_init(void)
{
	char	buff_env[4096];
	t_sh	*sh;

	sh = t_sh_recover();
	if (tcgetattr(0, &sh->default_term))
		prompt_error();
	if ((sh->term_name = getenv("TERM")) == NULL)
		prompt_error();
	if (tgetent(buff_env, sh->term_name) != 1)
		prompt_error();
	if (tcgetattr(0, &sh->term) == -1)
		prompt_error();
	sh->signals_disabled = 0;
	sh->term.c_lflag &= ~(ICANON | ECHO);
	sh->term.c_cc[VMIN] = 1;
	sh->term.c_cc[VTIME] = 0;
	sh->prompt_position = 0;
	if (tcsetattr(0, TCSADRAIN, &sh->term) == -1)
		prompt_error();
	prompt_update_window();
	return (1);
}

int		prompt_update_window(void)
{
	t_sh *sh;

	sh = t_sh_recover();
	return (ioctl(0, TIOCGWINSZ, &sh->win) != -1);
}

int		prompt_reset(void)
{
	t_sh *sh;

	sh = t_sh_recover();
	tputs(tgetstr("ve", NULL), 1, tputs_putchar);
	if (tcsetattr(0, TCSANOW, &sh->default_term) == -1)
		return (0);
	return (1);
}
