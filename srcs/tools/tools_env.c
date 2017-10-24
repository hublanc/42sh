#include "shell.h"

int			print_alloc_error(char *str)
{
	ft_putendl_fd(str, 2);
	return (1);
}

int			error_env(size_t *i)
{
	free(i);
	return (1);
}

void		end_ft_env(size_t *i, char **env)
{
	if (i[2])
		env_tab(env);
	free(i);
}
