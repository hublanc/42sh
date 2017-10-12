/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:46:11 by nbouchin          #+#    #+#             */
/*   Updated: 2017/10/12 14:24:48 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

//a supprimer apres merge cd
static char	*get_elem(char ***env, char *elem)
{
	int	i;

	if		(!env || !*env || !**env)
		return (NULL);
	i = 0;
	while ((*env)[i] && ft_strncmp((*env)[i], elem, ft_strlen(elem)))
		i++;
	if (!(*env)[i])
		return (NULL);
	return ((*env)[i] + ft_strlen(elem));
}

char	*split_prompt(char *str)
{
	int		i;
	int		count_slash;
	char	*ret;

	count_slash = 0;
	i = ft_strlen(str);
	while (count_slash != 2 && i--)
	{
		if (str[i] == '/')
			count_slash += 1;
	}
	ret = ft_strsub(str, i + 1, ft_strlen(str));
	(str) ? ft_strdel(&str) : 0;
	return (ret);
}

int		print_prompt(void)
{
	char	*prompt;
	char	*tmp;
	t_loc	*local;
	size_t	size;

	tmp = NULL;
	if (!(local = get_loc("PS1")))
	{
		if (!(tmp = get_elem(save_env(NULL), "PS1=")))
		{
			add_loc("PS1", "\\h @ \\W\\$ > ");
			local = get_loc("PS1");
		}
	}
	(!tmp && local && local->value) ? tmp = local->value : 0;
	prompt = (tmp) ? ft_strdup(tmp) : ft_strdup("42sh> ");
	prompt_management(&prompt);
	ft_putstr(prompt);
	size = ft_strlen(prompt);
	ft_strdel(&prompt);
	return (size);
}

char	*return_prompt(void)
{
	char	*prompt;
	char	*tmp;
	t_loc	*local;

	tmp = NULL;
	if (!(local = get_loc("PS1")))
	{
		if (!(tmp = get_elem(save_env(NULL), "PS1=")))
		{
			add_loc("PS1", "\\h @ \\W\\$ > ");
			local = get_loc("PS1");
		}
	}
	(!tmp && local && local->value) ? tmp = local->value : 0;
	prompt = (tmp) ? ft_strdup(tmp) : ft_strdup("42sh> ");
	prompt_management(&prompt);
	return (prompt);
}
