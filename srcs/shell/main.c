#include <shell.h>

t_sh	*t_sh_recover(void)
{
	static t_sh	sh;

	return (&sh);
}

static	void	prepare_env(void)
{
	char 	*number;
	t_sh	*sh;

	sh = t_sh_recover();
	if (env_get(sh->env_list, "SHLVL"))
		number = ft_itoa(ft_atoi(env_get(sh->env_list, "SHLVL")) + 1);
	else
		number = ft_itoa(1);
	env_set(&sh->env_list, "SHLVL", number);
	if (number)
		free(number);
}

static int		shell(void)
{
	char	*input;
	int		is_last_cmd_empty;

	UNUSED(input);
	is_last_cmd_empty = 0;
	while (1)
	{
		
	}
	return (0);
}

int  	main(int argc, char **argv, char **environ)
{
	t_sh	*sh;

	UNUSED(argv);
	sh = t_sh_recover();
	sh->tty = open("/dev/tty", O_RDWR);
	if (argc > 1)
	{
		ft_putendl_fd("42sh cannot execute commands", 2);
		return (0);
	}
	sh->env_list = NULL;
	env_to_list(&sh->env_list, environ);
	prepare_env();
	return (shell());
}