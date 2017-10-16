/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 14:08:53 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/13 13:44:08 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
 **	Ctrl C a gerer quand on mettra dans le shell
 */

int		put_my_char(int c)
{
	write(1, &c, 1);
	return (1);
}

char	*read_r_opt(void)
{
	char	buf[2];
	char	*readding;

	set_terminal();
	readding = ft_strnew(0);
	while (1)
	{
		ft_bzero(buf, 2);
		read(0, buf, 2);
		if (buf[0] == 10)
			break ;
		else if (buf[0] == 127 && !buf[1])
		{
			if (readding)
			{
				tputs(tgetstr("le", NULL), 1, &put_my_char);
				tputs(tgetstr("cd", NULL), 1, &put_my_char);
				readding[ft_strlen(readding) - 1] = '\0';
			}
		}
		else if (ft_isprint(buf[0]) && !buf[1])
		{
			ft_putchar(buf[0]);
			readding = ft_strapp(readding, buf);
		}
	}
	reset_term();
	return (readding);
}

char	*read_without_opt(void)
{
	char	*readding;
	char	buf[2];
	int		backslash;

	backslash = 0;
	set_terminal();
	readding = ft_strnew(0);
	while (1)
	{
		ft_bzero(buf, 2);
		read(0, buf, 2);
		if (buf[0] == 10 && !backslash)
			break ;
		else if (buf[0] == 10 && backslash)
		{
			ft_putstr_fd("\n> ", 2);
			backslash = 0;
		}
		else if (buf[0] == 127 && !buf[1])
		{
			if (readding)
			{
				tputs(tgetstr("le", NULL), 1, &put_my_char);
				tputs(tgetstr("cd", NULL), 1, &put_my_char);
				readding[ft_strlen(readding) - 1] = '\0';
			}
		}
		else if (buf[0] == '\\')
		{
			ft_putchar(buf[0]);
			if (!backslash)
				backslash = 1;
			else
				readding = ft_strapp(readding, buf);
		}
		else if (ft_isprint(buf[0]) && !buf[1])
		{
			ft_putchar(buf[0]);
			readding = ft_strapp(readding, buf);
		}
	}
	reset_term();
	return (readding);
}

int		get_read_opt(char **cmd)
{
	int	size;
	int	ret;
	int	opt;

	opt = 0;
	size = 0;
	while (cmd[size])
		size++;
	while ((ret = ft_getopt(size, (const char**)cmd, "r")) != -1)
		opt = ret;
	return (opt);
}

int		valid_local_var(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		while (cmd[i][j])
		{
			if (!ft_isalnum(cmd[i][j]) && cmd[i][j] != '_')
			{
				ft_putstr("\nshell: read: `");
				ft_putstr(cmd[i]);
				ft_putendl("': not a valid identifier");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

char            **prep_setenv(char *name, char *value)
{
	char            **tab;

	tab = (char**)ft_memalloc(sizeof(char*) * 4);
	tab[0] = ft_strdup("setenv");
	if (name)
		tab[1] = ft_strdup(name);
	if (value)
		tab[2] = ft_strdup(value);
	tab[3] = NULL;
	return (tab);
}

int		read_put_in_var(char **cmd, char *readding)
{
	char	**split;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strnew(0);
	if (!valid_local_var(&cmd[g_optind]))
		return (1);
	if (!(split = ft_strsplit(readding, ' ')))
		return (1);
	ft_putchar('\n');
	while (cmd[g_optind + 1])
		add_loc(cmd[g_optind++], split[i++]);
	while (split[i])
	{
		tmp = ft_strapp(tmp, split[i]);
		tmp = (split[i + 1]) ? ft_strapp(tmp, " ") : tmp;
		i++;
	}
	add_loc(cmd[g_optind], tmp);
	ft_strdel(&tmp);
	del_tabstr(&split);
	return (0);
}

char	**default_mod(void)
{
	char	**new_cmd;

	if (!(new_cmd = (char**)ft_memalloc(sizeof(char*) * 2)))
		exit(EXIT_FAILURE);
	new_cmd[0] = ft_strdup("REPLY");
	new_cmd[1] = NULL;
	return (new_cmd);
}

int		ft_read(char **cmd, char ***env)
{
	int		opt;
	int		default_read;
	char	*readding;
	int		error;

	(void)env;
	default_read = 0;
	readding = NULL;
	g_optind = 0;
	opt = get_read_opt(cmd);
	if (cmd && !cmd[g_optind])
	{
		default_read = 1;
		cmd = default_mod();
	}
	if (opt != 0 && opt != 'r')
		return (2);
	if (opt == 'r')
		readding = read_r_opt();
	else
		readding = read_without_opt();
	error = read_put_in_var(cmd, readding);
	if (default_read)
		del_tabstr(&cmd);
	ft_strdel(&readding);
	if (error)
		return (error);
	return (0);
}
