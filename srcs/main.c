/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 16:37:30 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/23 10:37:19 by mameyer          ###   ########.fr       */
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

char		**init_env(void)
{
	char		**new;
	char		*pwd;
	char		*tmp;

	if (!(new = (char**)ft_memalloc(sizeof(char*) * 4)))
		return (NULL);
	pwd = ft_strdup("PWD=");
	tmp = getcwd(NULL, PATH_MAX + 1);
	pwd = ft_strapp(pwd, tmp);
	new[0] = ft_strdup(pwd);
	new[1] = ft_strdup("SHLVL=1");
	new[2] = ft_strdup("_=/usr/bin/env");
	new[3] = NULL;
	ft_strdel(&tmp);
	ft_strdel(&pwd);
	return (new);
}

int			main(int ac, char **av, char **env)
{
	t_cmd		cmd;
	t_control	*history;
	char		**cp_env;
	int			status;

	cp_env = NULL;
	if (ac != 1)
		return (-1);
	(void)ac;
	(void)av;
	cp_env = (*env) ? get_env(env, 1) : init_env();
	if (cp_env == NULL)
		return (-1);
	save_env(&cp_env);
	signal(SIGINT, get_signal);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGKILL, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	set_terminal();

	 /*test
	//FIN TEST*/

	status = 0;
	print_prompt();
	cmd = init_cmd(return_prompt());
	save_cmd(&cmd);
	history = NULL;
	history = load_history(env);
	while (1)
		key_handler(&cmd, &history, save_env(NULL));
	del_tabstr(&cp_env);
}
