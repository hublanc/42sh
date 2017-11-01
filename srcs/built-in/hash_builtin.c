/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 18:48:25 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/01 11:26:01 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			check_opt_hash(char **tab, char *opt)
{
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
		if (!ft_strcmp(tab[i], "-r"))
			*opt = 'r';
		else
		{
			ft_putstr_fd("hash: bad option : ", 2);
			ft_putendl_fd(tab[i], 2);
			return (0);
		}
		i++;
	}
	return (i);
}

int			try_addht(char *value, char **env)
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
	del_tabstr(&bin);
	return (1);
}

int			disp_hash(void)
{
	t_hash		**hash;
	t_hash		*tmp;

	hash = singleton_hash();
	tmp = *hash;
	if (!tmp)
		ft_putstr_fd("hash: hash table empty\n", 2);
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
		status = try_addht(tab[i++], env);
	return (status);
}
