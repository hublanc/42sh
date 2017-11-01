/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 11:40:20 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/01 11:14:19 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			read_terminfo(char *tmp)
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
			closedir(dirp2);
			return (1);
		}
	}
	closedir(dirp2);
	return (0);
}

int			get_terminfo(void)
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
			(tmp) ? free(tmp) : 0;
			closedir(dirp);
			return (0);
		}
		if (read_terminfo(tmp) == 1)
		{
			closedir(dirp);
			free(tmp);
			return (1);
		}
		free(tmp);
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
	g_term = term;
	term.c_lflag &= ~(ECHO | ICANON);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &term);
}

void		reset_term(void)
{
	tcsetattr(0, TCSADRAIN, &g_term);
}

void		reset_disp(void)
{
	tputs(tgetstr("cl", NULL), 1, tputchar);
}
