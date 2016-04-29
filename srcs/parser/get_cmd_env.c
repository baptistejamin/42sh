/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 15:20:50 by ngrasset          #+#    #+#             */
/*   Updated: 2016/04/29 15:56:22 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <shell.h>

char	*get_cmd_env(char *cmd, char *var_raw)
{
	char	*right;
	char	*var;
	char	*env_value;
	int		i;
	t_sh	*shell;

	env_value = NULL;
	shell = t_sh_recover();
	*var_raw = '\0';
	i = 1;
	while (ft_isalnum(var_raw[i]) || var_raw[i] == '?' || var_raw[i] == '_')
		i++;
	right = var_raw + i;
	var = ft_strsub(var_raw, 1, i > 0 ? i - 1 : i);
	env_value = env_get(shell->env_list, var);
	if (!env_value || (env_value && !*(env_value)))
		env_value = env_get(shell->vars_list, var);
	cmd = ft_strfjoin(cmd, env_value);
	if (right && *right)
		cmd = ft_strfjoin(cmd, right);
	if (var)
		free(var);
	return (cmd);
}
