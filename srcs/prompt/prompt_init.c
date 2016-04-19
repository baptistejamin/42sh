/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/19 20:25:54 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <prompt.h>

void	prompt_error(void)
{
	ft_putendl("Termcaps. Cannot launch 42sh. Did you set env vars?");
	exit(1);
}

void	prompt_add_new(void)
{
	t_sh		*sh;
	t_prompt	prompt;

	sh = t_sh_recover();
	prompt.chars = NULL;
	prompt.cursor_index = 0;
	prompt.copy_mode = 0;
	prompt.copy_start = 0;
	prompt.copy_end = 0;
	prompt.copy_word = NULL;
	prompt.lenght = 0;
	ft_lstadd(&sh->history, ft_lstnew(&prompt, sizeof(t_prompt)));
	sh->c_prompt = sh->history->content;
}

int		prompt_init(void)
{
	char	buff_env[4096];
	t_sh	*sh;

	sh = t_sh_recover();
	if ((sh->term_name = getenv("TERM")) == NULL)
		prompt_error();
	if (tgetent(buff_env, sh->term_name) != 1)
		prompt_error();
	if (tcgetattr(0, &sh->term) == -1)
		prompt_error();
	if (tcgetattr(0, &sh->default_term))
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
	sh->term.c_lflag = (ICANON | ECHO | ISIG);
	sh->signals_disabled = 1;
	if (tcsetattr(0, TCSANOW, &sh->term) == -1)
		return (0);
	tputs(tgetstr("ve", NULL), 1, tputs_putchar);
	return (1);
}
