#include "shell.h"

static void	prep_complstar2(t_compl *compl, t_cmd *cmd)
{
	if (compl->arg)
		go_right(cmd);
	if (compl->path[ft_strlen(compl->path) - 1] == '/')
		compl->path[ft_strlen(compl->path) - 1] = 0;
	if (!compl->isslash)
	{
		cmd->str = ft_strdelone(cmd->str, cmd->col - 1 - cmd->prlen);
		go_left(cmd);
	}
}

static void	prep_complstar(t_compl *compl, t_cmd *cmd)
{
	cmd->str = ft_strdelone(cmd->str, cmd->col - 1 - cmd->prlen);
	go_left(cmd);
	if (compl->arg && compl->arg[0] && compl->isstar > 1)
	{
		while (compl->arg[ft_strlen(compl->arg - 1)] ==
				cmd->str[cmd->col - 1 - cmd->prlen])
		{
			cmd->str = ft_strdelone(cmd->str, cmd->col - 1 - cmd->prlen);
			go_left(cmd);
		}
		if (cmd->str[cmd->col - 1 - cmd->prlen] == '/')
			cmd->str = ft_strdelone(cmd->str, cmd->col - 1 - cmd->prlen);
	}
}

static int	compl_star2(t_compl *compl, t_cmd *cmd)
{
	t_coargs	*ar;
	char		*tmp;
	char		*tmp2;

	prep_complstar2(compl, cmd);
	ar = &compl->args;
	tmp2 = ft_strjoin("/", ar->arg);
	tmp = ft_strjoin(tmp2, " ");
	(tmp2) ? free(tmp2) : 0;
	while (ar && (ar = ar->next))
	{
		tmp2 = ft_strjoin(tmp, compl->path);
		(tmp) ? free(tmp) : 0;
		tmp = ft_strjoin(tmp2, "/");
		(tmp2) ? free(tmp2) : 0;
		tmp2 = ft_strjoin(tmp, ar->arg);
		(tmp) ? free(tmp) : 0;
		tmp = ft_strjoin(tmp2, " ");
		(tmp2) ? free(tmp2) : 0;
	}
	add_line(cmd, tmp);
	return (1);
}

int			compl_star(t_compl *compl, t_cmd *cmd)
{
	t_coargs	*ar;
	char		*tmp;
	char		*tmp2;

	if (!compl->isstar)
		return (0);
	prep_complstar(compl, cmd);
	if (compl->isstar == 2 || (compl->isstar == 3 && compl->path))
		return (compl_star2(compl, cmd));
	ar = &compl->args;
	tmp = ft_strjoin(ar->arg, " ");
	while (ar && (ar = ar->next) && ar->arg)
	{
		tmp2 = ft_strjoin(tmp, ar->arg);
		(tmp) ? free(tmp) : 0;
		tmp = ft_strjoin(tmp2, " ");
		(tmp2) ? free(tmp2) : 0;
	}
	add_line(cmd, tmp);
	(tmp) ? free(tmp) : 0;
	return (1);
}
