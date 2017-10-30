/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:13:41 by amazurie          #+#    #+#             */
/*   Updated: 2017/10/30 11:31:27 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	check_pwd2(char *path, char ***env, char *rep, char *tmp)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strschr_len(tmp, path);
	while (tmp[j] == path[i++])
		ssupprchr(&tmp, j);
	i = 0;
	while (rep[i])
		saddchr(&tmp, rep[i++], j++);
	if (ft_strcmp(tmp, get_elem(env, "PWD=")) != 0)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(tmp, 2);
		ft_putchar_fd('\n', 2);
	}
	else
	{
		i = ft_strlen(get_elem(env, "HOME="));
		while (tmp[0] && i-- > 0)
			ssupprchr(&tmp, 0);
		ft_putchar('~');
		ft_putstr(tmp);
		ft_putchar('\n');
	}
}

static int	check_pwd(char *path, char ***env, char *rep)
{
	char	*tmp;
	char	*tmp2;

	if (!get_elem(env, "HOME="))
	{
		ft_putstr_fd("cd: HOME not set.\n", 2);
		return (0);
	}
	else if (!(tmp = ft_strdup(get_elem(env, "PWD=")))
			|| (tmp2 = ft_strschr(tmp, path)) == 0)
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putchar_fd('\n', 2);
	}
	else
		check_pwd2(path, env, rep, tmp);
	if (tmp)
		free(tmp);
	return (0);
}

static char	*cd2(char **path, char ***env, int i)
{
	char	*tmp;

	tmp = NULL;
	if (!path[i] || !ft_strcmp(path[i], "~") || (path[i][0] == '~'
			&& path[i][1] == '/' && !path[i][2])
			|| (path[i][0] == '-' && path[i][1] == '-'))
	{
		if (!get_elem(env, "HOME="))
			ft_putstr_fd("cd: HOME not set.\n", 2);
		else
			tmp = ft_strdup(get_elem(env, "HOME="));
	}
	else if (ft_strcmp(path[i], "-") == 0)
	{
		if (!get_elem(env, "OLDPWD="))
		{
			ft_putstr_fd("cd: OLDPWD not set.\n", 2);
			return (NULL);
		}
		else
			tmp = ft_strdup(get_elem(env, "OLDPWD="));
	}
	else
		tmp = ft_strdup(path[i]);
	return (tmp);
}

static int	check_cdopt(char **path, char *opt)
{
	int	i;
	int	ret;

	i = 0;
	while (path[i])
		i++;
	g_optind = 1;
	while ((ret = ft_getopt(i, (const char**)path, "LP")) != -1)
	{
		*opt = ret;
		if (*opt == '?')
			return (-1);
	}
	return (g_optind);
}

/*
**	zsh ignore les options si elles l'une est fausse
*/

int			cd(char **path, char ***env)
{
	char	*tmp;
	char	opt;
	int		i;
	int		j;

	if (!path || !path[0])
		return (1);
	check_isenvpwd(env);
	if ((i = check_cdopt(path, &opt)) == -1)
		return (1);
	j = 0;
	while (path[i + j])
		j++;
	if (j > 2)
		ft_putstr_fd("cd: too many arguments\n", 2);
	else if (j == 2)
		return (check_pwd(path[i], env, path[i + 1]));
	else
	{
		if (!(tmp = cd2(path, env, i)))
			return (-1);
		if (tmp)
			if (change_pwd(tmp, env, opt) && path[i]
					&& !ft_strcmp(path[i], "-"))
				ft_putendl(get_elem(env, "PWD="));
		free(tmp);
	}
	return (0);
}
