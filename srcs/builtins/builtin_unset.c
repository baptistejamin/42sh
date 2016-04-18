/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/18 19:53:05 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

int		builtin_unset_error_missing(void)
{
	ft_putendl_fd("unsetenv: You must provide a variable", 2);
	return (2);
}

int		builtin_unset_error_two_many(void)
{
	ft_putendl_fd("unsetenv: Two many arguments", 2);
	return (2);
}

void	builtin_unset_free(void *content, size_t size)
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

void	builtin_unset_one(char *var)
{
	t_sh		*sh;
	t_env		*env;
	t_list		*cur;
	int			i;

	sh = t_sh_recover();
	cur = sh->vars_list;
	i= 0;
	while (cur)
	{
		env = cur->content;
		cur = cur->next;
		if (ft_strcmp(var, env->var) == 0)
			ft_lstdel_at(&sh->vars_list, i, &builtin_unsetenv_free);
		i++;
	}
}

int		builtin_unset(t_list *environ, char **cmds)
{
	int	i;

	UNUSED(environ);
	if (!cmds[1])
		return (builtin_unset_error_missing());
	i = 1;
	while (cmds[i])
	{
		builtin_unset_one(cmds[i]);
		i++;
	}
	return (0);
}
