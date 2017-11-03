/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 16:37:30 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/03 15:49:13 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char		***save_env(char ***env)
{
	static char ***s_env = NULL;

	if (env)
		s_env = env;
	return (s_env);
}

static char	**init_env(void)
{
	char		**new;
	char		*pwd;
	char		*tmp;

	if (!(new = (char**)ft_memalloc(sizeof(char*) * 5)))
		return (NULL);
	pwd = ft_strdup("PWD=");
	tmp = getcwd(NULL, PATH_MAX + 1);
	pwd = ft_strapp(pwd, tmp);
	new[0] = ft_strdup(pwd);
	new[1] = ft_strdup("SHLVL=1");
	new[2] = ft_strdup("_=/usr/bin/env");
	new[4] = NULL;
	ft_strdel(&tmp);
	ft_strdel(&pwd);
	return (new);
}

static void	add_startenv(char ***env)
{
	char	*tab[4];

	tab[0] = "setenv";
	tab[1] = "CLICOLOR";
	tab[2] = "true";
	tab[3] = NULL;
	ft_setenv(tab, env);
}

static void	init_signal(void)
{
	signal(SIGINT, get_signal);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGKILL, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}

int			main(int ac, char **av, char **env)
{
	t_cmd		cmd;
	t_control	*history;
	char		**cp_env;

	cp_env = NULL;
	if (ac != 1)
		return (-1);
	(void)ac;
	(void)av;
	cp_env = (*env) ? get_env(env, 1) : init_env();
	if (cp_env == NULL)
		return (-1);
	add_startenv(&cp_env);
	save_env(&cp_env);
	init_signal();
	set_terminal();
	print_prompt();
	cmd = init_cmd(return_prompt());
	save_cmd(&cmd);
	history = NULL;
	history = load_history(env);
/*
**	TEST
*/
	char 		*str = ft_strdup("!ls:2-");
	char 		*new = NULL;
	char 		**bite;
	t_bang2		*bang;

	if (!(bang = malloc(sizeof(t_bang))))
		exit(-1);
	bang->str = ft_strdup("!ls:^-*");
	bang->dash = 1;
	bang->x = 0;
	bang->y = 0;
	bang->c_x = 0;
	bang->c_y = '*';

	if (!(bite = (char **)malloc(sizeof(char *) * 6)))
		exit(-1);
	bite[0] = ft_strdup("ls");
	bite[1] = ft_strdup("-l");
	bite[2] = ft_strdup("-a");
	bite[3] = ft_strdup("-r");
	bite[4] = ft_strdup("-1");
	bite[5] = NULL;
	designator_fnc(bite, bang);
	//new = deal_bang(str, history);
	return (0);

	(void)new;
	(void)str;
	while (1)
		key_handler(&cmd, &history, save_env(NULL));
	saved_loc(1);
	del_tabstr(&cp_env);
}
