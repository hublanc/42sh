/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 11:28:19 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/19 18:55:03 by hublanc          ###   ########.fr       */
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

void		stop_shell(char ***env, char **tab, t_control **history)
{
	char	*hist_file;

	hist_file = get_history_file(env);
	if (tab)
		del_tabstr(&tab);
	del_tabstr(env);
	if (hist_file)
	{
		rewrite_hist_file(history, hist_file);
		free(hist_file);
	}
	if (*history)
		*history = dll_clear_list(*history);
	reset_term();
	ft_putendl_fd("exit", 2);
	if (return_status() == 256)
		exit(1);
	exit(return_status());
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
