/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 18:48:25 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/13 13:42:41 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	check_opt_hash(char **tab, char *opt)
{
	char	*tmp;
	int		i;

	i = 1;
	*opt = 0;
	while (tab && tab[i] && tab[i][0] == '-')
	{
		if (!ft_strcmp(tab[i], "--"))
		{
			i++;
			break ;
		}
		tmp = tab[i];
		while (*(++tmp) == 'r' && *tmp && (tmp = ft_strchr(tmp, 'r')))
			*opt = 'r';
		if (tab[i][1] && (tmp && *tmp && *tmp != 'r'))
		{
			ft_putstr_fd("shell: hash: bad option : -", 2);
			ft_putchar_fd(*tmp, 2);
			ft_putchar_fd('\n', 2);
			return (0);
		}
		i++;
	}
	return (i);
}

static void	try_addht_notfound(char *value)
{
	ft_putstr_fd("shell: hash: ", 2);
	ft_putstr_fd(value, 2);
	ft_putstr_fd(": not found \n", 2);
}

static int	try_addht(char *value, char **env)
{
	char		**bin;
	int			i;

	i = 0;
	if (value && ft_strchr(value, '/'))
		return (1);
	bin = get_bin(env, in_env("PATH", env));
	while (bin && bin[i])
	{
		bin[i] = ft_strapp(bin[i], "/");
		bin[i] = ft_strapp(bin[i], value);
		if (check_access(bin[i]) == 1)
			break ;
		i++;
	}
	if (bin && bin[i])
	{
		add_hash_table(bin[i], value);
		del_tabstr(&bin);
		return (0);
	}
	else
		try_addht_notfound(value);
	del_tabstr(&bin);
	return (1);
}

static int	disp_hash(void)
{
	t_hash		**hash;
	t_hash		*tmp;

	hash = singleton_hash();
	tmp = *hash;
	if (!tmp)
		ft_putstr_fd("shell: hash: hash table empty\n", 2);
	while (tmp)
	{
		ft_putstr(tmp->value);
		ft_putstr("=");
		ft_putendl(tmp->path);
		tmp = tmp->next;
	}
	return (0);
}

int			hash_built(char **tab, char **env)
{
	char	opt;
	int		i;
	int		status;
	t_hash	**list;

	i = 1;
	status = 0;
	list = singleton_hash();
	if (len_array(tab) == 1)
		return (disp_hash());
	if ((i = check_opt_hash(tab, &opt)) == 0)
		return (1);
	if (opt == 'r')
		del_hash(list);
	while (tab && tab[i])
	{
		if (!builtin_tab(tab[i]))
			status = try_addht(tab[i], env);
		i++;
	}
	return (status);
}
