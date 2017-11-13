/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 11:40:20 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/13 13:47:06 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	change_termenv(char *name)
{
	char	***env;
	char	*tab[4];

	if (!(env = save_env(NULL)))
		return ;
	tab[0] = "setenv";
	tab[1] = "TERM";
	tab[2] = name;
	tab[3] = NULL;
	ft_setenv(tab, env);
}

static int	read_terminfo(char *tmp)
{
	struct dirent	*dirc;
	DIR				*dirp2;

	if (!(dirp2 = opendir(tmp)))
		return (0);
	while ((dirc = readdir(dirp2)))
	{
		if (tgetent(NULL, dirc->d_name) > 0 && tgetstr("do", NULL)
				&& tgetstr("nd", NULL) && tgetstr("mr", NULL)
				&& tgetstr("me", NULL) && tgetstr("up", NULL)
				&& tgetstr("cd", NULL) && tgetstr("cr", NULL)
				&& tgetstr("sc", NULL) && tgetstr("rc", NULL)
				&& tgetstr("ho", NULL) && tgetstr("le", NULL)
				&& tgetstr("cl", NULL))
		{
			change_termenv(dirc->d_name);
			closedir(dirp2);
			return (1);
		}
	}
	closedir(dirp2);
	return (0);
}

static int	get_terminfo(void)
{
	struct dirent	*dirc;
	DIR				*dirp;
	char			*tmp;

	if (!(dirp = opendir("/usr/share/terminfo")))
		return (0);
	while ((dirc = readdir(dirp)))
	{
		tmp = ft_strjoin("/usr/share/terminfo/", dirc->d_name);
		if (!tmp)
		{
			(tmp) ? ft_strdel(&tmp) : 0;
			closedir(dirp);
			return (0);
		}
		if (read_terminfo(tmp) == 1)
		{
			closedir(dirp);
			ft_strdel(&tmp);
			return (1);
		}
		ft_strdel(&tmp);
	}
	closedir(dirp);
	return (0);
}

void		set_terminal(void)
{
	struct termios	term;
	char			*name_term;

	name_term = getenv("TERM");
	if (((!name_term || !*name_term) || tgetent(NULL, name_term) == -1)
			&& !get_terminfo())
	{
		ft_putstr_fd("Could not load TERM, exiting...\n", 2);
		exit(EXIT_FAILURE);
	}
	tcgetattr(0, &term);
	check_in(term);
}

void		reset_term(void)
{
	tcsetattr(0, TCSADRAIN, &g_term);
}
