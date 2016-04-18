/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 18:32:25 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/18 16:08:10 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

void	shell_exit(void)
{
	t_sh *sh;

	sh = t_sh_recover();
	if (sh->env_list)
	{
		free(sh->env_list);
	}
	prompt_reset();
	exit(sh->last_res);
}
