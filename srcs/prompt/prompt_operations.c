/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/29 19:47:59 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <prompt.h>

t_prompt	*prompt_create_new(void)
{
	t_prompt	*prompt;

	prompt = malloc(sizeof(t_prompt));
	prompt->chars = NULL;
	prompt->cursor_index = 0;
	prompt->copy_mode = 0;
	prompt->copy_start = 0;
	prompt->copy_end = 0;
	prompt->copy_word = NULL;
	prompt->lenght = 0;
	return (prompt);
}

void		prompt_current_reset(void)
{
	t_prompt	*prompt;

	prompt = t_sh_recover()->c_prompt;
	prompt->chars = NULL;
	prompt->cursor_index = 0;
	prompt->copy_mode = 0;
	prompt->copy_start = 0;
	prompt->copy_end = 0;
	prompt->copy_word = NULL;
	prompt->lenght = 0;
}

void		prompt_add_command(int is_last_cmd_empty)
{
	t_sh		*sh;
	t_prompt	*prompt;

	prompt = prompt_create_new();
	sh = t_sh_recover();
	if (!is_last_cmd_empty)
	{
		ft_lstcpy(&prompt->chars, sh->c_prompt->chars);
		ft_lstrev(&prompt->chars);
		prompt->lenght = sh->c_prompt->lenght;
		prompt->cursor_index = prompt->lenght;
		ft_lstadd(&sh->history, ft_lstnew(prompt, sizeof(t_prompt)));
		sh->prompt_position--;
	}
}
