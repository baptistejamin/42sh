/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/11 20:38:32 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <prompt.h>

enum e_prompt_status	prompt_copy_mode(char *buf)
{
	t_sh	*sh;

	sh = t_sh_recover();
	if (!COPY_MODE)
		return (TRYING);
	sh->c_prompt->copy_mode = 1;
	sh->c_prompt->copy_start = sh->c_prompt->cursor_index;
	sh->c_prompt->copy_end = sh->c_prompt->cursor_index;
	return (READING);
}

enum e_prompt_status	prompt_copy(char *buf)
{
	t_sh	*sh;

	sh = t_sh_recover();
	if (!COPY)
		return (TRYING);
	if (!sh->c_prompt->copy_mode)
		return (TRYING);
	sh->c_prompt->copy_mode = 0;
	sh->c_prompt->copy_word = prompt_get_command(
		sh->c_prompt, sh->c_prompt->copy_start, sh->c_prompt->copy_end + 1);
	sh->c_prompt->copy_start = 0;
	sh->c_prompt->copy_end = 0;
	prompt_display(1);
	return (READING);
}

enum e_prompt_status	prompt_cut(char *buf)
{
	t_sh	*sh;
	int		i;

	i = 0;
	sh = t_sh_recover();
	if (!CUT)
		return (TRYING);
	if (!sh->c_prompt->copy_mode)
		return (TRYING);
	sh->c_prompt->copy_mode = 0;
	sh->c_prompt->copy_word = prompt_get_command(
		sh->c_prompt, sh->c_prompt->copy_start, sh->c_prompt->copy_end + 1);
	i = sh->c_prompt->copy_end;
	while (sh->c_prompt->copy_start < i)
	{
		ft_lstdel_at(&sh->c_prompt->chars, i - 1, &free_char);
		sh->c_prompt->cursor_index--;
		sh->c_prompt->lenght--;
		i--;
	}
	sh->c_prompt->copy_start = 0;
	sh->c_prompt->copy_end = 0;
	prompt_display(1);
	return (READING);
}

enum e_prompt_status	prompt_paste(char *buf)
{
	t_sh	*sh;
	int		i;

	i = 0;
	sh = t_sh_recover();
	if (!PASTE)
		return (TRYING);
	if (!sh->c_prompt->copy_word)
		return (TRYING);
	sh->c_prompt->copy_mode = 0;
	while (sh->c_prompt->copy_word[i])
	{
		prompt_insert_one_char(sh->c_prompt->copy_word[i]);
		i++;
	}
	sh->c_prompt->copy_start = 0;
	sh->c_prompt->copy_end = 0;
	prompt_display(1);
	return (READING);
}
