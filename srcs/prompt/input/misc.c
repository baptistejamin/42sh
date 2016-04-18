/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/18 16:06:59 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>
#include <prompt.h>

enum e_prompt_status	prompt_fire_cmd(char *buf)
{
	if (!ENTER)
		return (TRYING);
	prompt_display(0);
	tputs(tgetstr("do", NULL), 0, tputs_putchar);
	return (FIRE_CMD);
}

enum e_prompt_status	prompt_shell_quit(char *buf)
{
	if (!QUIT)
		return (TRYING);
	shell_exit();
	return (READING);
}

void					free_char(void *content, size_t size)
{
	UNUSED(size);
	free(content);
}
