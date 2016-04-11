/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chars_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/11 20:43:00 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <prompt.h>

enum e_prompt_status	prompt_move_up(char *buf)
{
	t_sh	*sh;

	sh = t_sh_recover();
	if (!SHIFT_UP)
		return (TRYING);
	if (sh->c_prompt->cursor_index - sh->win.ws_col >= 0)
		sh->c_prompt->cursor_index -= sh->win.ws_col;
	else
		sh->c_prompt->cursor_index = 0;
	prompt_display(1);
	return (READING);
}

enum e_prompt_status	prompt_move_down(char *buf)
{
	t_sh	*sh;

	sh = t_sh_recover();
	if (!SHIFT_DOWN)
		return (TRYING);
	if (sh->c_prompt->cursor_index + sh->win.ws_col <=
		sh->c_prompt->lenght)
		sh->c_prompt->cursor_index += sh->win.ws_col;
	else
		sh->c_prompt->cursor_index = sh->c_prompt->lenght;
	prompt_display(1);
	return (READING);
}

enum e_prompt_status	prompt_move_right(char *buf)
{
	t_sh	*sh;

	sh = t_sh_recover();
	if (!RIGHT)
		return (TRYING);
	if (sh->c_prompt->cursor_index < sh->c_prompt->lenght)
	{
		sh->c_prompt->cursor_index++;
		if (sh->c_prompt->copy_mode)
			sh->c_prompt->copy_end++;
		prompt_display(1);
	}
	else
		tputs(tgetstr("bl", NULL), 0, tputs_putchar);
	return (READING);
}

enum e_prompt_status	prompt_move_left(char *buf)
{
	t_sh	*sh;

	sh = t_sh_recover();
	if (!LEFT)
		return (TRYING);
	if (sh->c_prompt->cursor_index > 0)
	{
		sh->c_prompt->cursor_index--;
		prompt_display(1);
	}
	else
		tputs(tgetstr("bl", NULL), 0, tputs_putchar);
	return (READING);
}
