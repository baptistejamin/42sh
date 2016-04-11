/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjamin <bjamin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 14:06:11 by bjamin            #+#    #+#             */
/*   Updated: 2016/04/11 19:27:26 by bjamin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

char	*env_get(t_list *list, char *var)
{
	t_env	*env;
	t_list	*cur;

	cur = list;
	while (cur)
	{
		env = cur->content;
		if (ft_strcmp(var, env->var) == 0)
			return (env->value);
		cur = cur->next;
	}
	return ("");
}

void	env_show(t_list *list)
{
	t_env	*env;
	t_list	*cur;

	cur = list;
	while (cur)
	{
		env = cur->content;
		ft_putstr(env->var);
		ft_putstr("=");
		ft_putendl(env->value);
		cur = cur->next;
	}
}

void	env_to_list(t_list **list, char **environ)
{
	int		i;
	t_env	*env;

	i = 0;
	while (environ[i])
	{
		env = malloc(sizeof(t_env));
		env->var = ft_strnew(ft_strlen(environ[i]) -
			ft_strlen(ft_strchr(environ[i], '=') + 1));
		ft_strncpy(env->var, environ[i], ft_strlen(environ[i]) -
			ft_strlen(ft_strchr(environ[i], '=')));
		env->value = ft_strdup(ft_strchr(environ[i], '=') + 1);
		ft_lstadd(list, ft_lstnew(env, sizeof(t_env)));
		i++;
	}
}

char	**env_from_list(t_list *list)
{
	int		i;
	char	**environ;
	t_env	*env;

	environ = malloc(sizeof(char *) * (ft_lstcount(list) + 1));
	i = 0;
	while (list)
	{
		env = list->content;
		environ[i] = ft_strfjoin(ft_strjoin(env->var, "="), env->value);
		list = list->next;
		i++;
	}
	environ[i] = NULL;
	return (environ);
}
