/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 11:28:19 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/13 14:23:14 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		del_tabstr(char ***str)
{
	int		i;

	i = 0;
	if (!str || !*str)
		return ;
	while ((*str)[i])
		ft_strdel(&((*str)[i++]));
	free(*str);
	*str = NULL;
}

void		disp_tab(char **str)
{
	int		i;

	i = 0;
	if (!str || !*str)
		return ;
	while (str[i])
		ft_putendl(str[i++]);
}

int			len_array(char **str)
{
	int		len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

int			stop_shell(char ***env, char **tab, t_control **history)
{
	char	*hist_file;
	t_hash	**hash_table;
	int		status;

	if ((status = ft_exit(tab)) == -1)
		return (1);
	hash_table = singleton_hash();
	del_hash(hash_table);
	del_spath();
	hist_file = get_history_file(env);
	if (tab)
		del_tabstr(&tab);
	del_tabstr(env);
	if (hist_file)
	{
		rewrite_hist_file(history, hist_file);
		ft_strdel(&hist_file);
	}
	if (*history)
		*history = dll_clear_list(*history);
	saved_loc(NULL, 1);
	reset_term();
	exit(status > 255 ? status - 255 : status);
}

char		**get_env(char **env, int add)
{
	char		**new;
	int			len;
	int			i;

	len = 0;
	i = 0;
	if (!env)
		return (NULL);
	while (env[len])
		len++;
	if (!(new = (char**)ft_memalloc(sizeof(char*) * (len + add))))
		return (NULL);
	len = 0;
	while (env[len])
		new[i++] = ft_strdup(env[len++]);
	return (new);
}
