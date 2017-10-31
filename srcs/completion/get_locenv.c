/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_locenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 10:49:23 by amazurie          #+#    #+#             */
/*   Updated: 2017/10/31 13:28:35 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	new_coarg(t_compl *compl, t_coargs **args, char *name, int id)
{
	char		*tmp;

	if (!(tmp = ft_strjoin("$", name)))
		return ;
	(*args)->arg = add_handspace(tmp);
	compl->nbrargs++;
	if (ft_strlen((*args)->arg) + 1 > compl->maxlen)
		compl->maxlen = ft_strlen((*args)->arg) + 1;
	free(tmp);
	(*args)->id = id;
	(*args)->color = NULL;
	if (!((*args)->next = (t_coargs *)ft_memalloc(sizeof(t_coargs))))
	{
		(*args)->next = NULL;
		return ;
	}
	(*args) = (*args)->next;
	(*args)->arg = NULL;
	(*args)->next = NULL;
}

static void	get_complenv(t_compl *compl, t_coargs **args, char **env, int *id)
{
	char		*nametmp;
	int			i;

	i = -1;
	while (env[++i])
	{
		if (!compl->arg || (ft_strlen(compl->arg) - (compl->arg[0] == '$' ?
					1 : 0) < (size_t)ft_strlen_chr(env[i], '=')
				&& !check_lname(compl->arg + (compl->arg[0] == '$' ? 1 : 0),
					env[i], ft_strlen(compl->arg)
					- (compl->arg[0] == '$' ? 1 : 0))))
		{
			if (!(nametmp = ft_strndup(env[i], ft_strlen_chr(env[i], '='))))
				return ;
			new_coarg(compl, args, nametmp, (*id)++);
			free(nametmp);
		}
	}
}

static void	get_complloc(t_compl *compl, t_coargs **args, t_loc *loc, int *id)
{
	while (loc)
	{
		if (!compl->arg || !check_lname(compl->arg +
					(compl->arg[0] == '$' ? 1 : 0), loc->name,
					ft_strlen(compl->arg) - (compl->arg[0] == '$' ? 1 : 0)))
			new_coarg(compl, args, loc->name, (*id)++);
		loc = loc->next;
	}
}

void		get_locenv(t_compl *compl)
{
	t_coargs	*args;
	t_loc		*loc;
	char		**env;
	int			id;

	args = &compl->args;
	if (!compl->arg || compl->arg[0] == '$')
	{
		if ((id = new_complarg(&args)) == -1)
			return ;
		if ((env = *save_env(NULL)))
			get_complenv(compl, &args, env, &id);
		if ((loc = get_loc(NULL)))
			get_complloc(compl, &args, loc, &id);
	}
}
