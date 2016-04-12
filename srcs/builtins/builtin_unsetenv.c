/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/12 16:26:36 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int		builtin_unsetenv_error_missing(void)
{
	ft_putendl_fd("unsetenv: You must provide a variable", 2);
	return (2);
}

int		builtin_unsetenv_error_two_many(void)
{
	ft_putendl_fd("unsetenv: Two many arguments", 2);
	return (2);
}

void	builtin_unsetenv_free(void *content, size_t size)
{
	t_env		*env;

	UNUSED(size);
	env = content;
	if (!content)
		return ;
	if (env->var)
		free(env->var);
	if (env->value)
		free(env->value);
	free(env);
}

int		builtin_unsetenv(t_list *environ, char **cmds)
{
	t_sh		*sh;
	t_list		*cur;
	t_env		*env;
	int			i;

	sh = t_sh_recover();
	UNUSED(environ);
	if (!cmds[1])
		return (builtin_unsetenv_error_missing());
	if (cmds[2])
		return (builtin_unsetenv_error_two_many());
	i = 0;
	cur = sh->env_list;
	while (cur)
	{
		env = cur->content;
		cur = cur->next;
		if (ft_strcmp(cmds[1], env->var) == 0)
		{
			ft_lstdel_at(&sh->env_list, i, &builtin_unsetenv_free);
			return (0);
		}
		i++;
	}
	return (0);
}
