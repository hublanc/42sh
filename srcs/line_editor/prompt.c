/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:46:11 by nbouchin          #+#    #+#             */
/*   Updated: 2017/10/10 15:38:06 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	t_loc	*local;

	if (!(local = get_loc("PS1")))
	{
		add_loc("PS1", "\\h @ \\W\\$ > ");
		local = get_loc("PS1");
	}
	prompt = (local && local->value) ? ft_strdup(local->value) : ft_strdup("42sh> ");
	prompt_management(&prompt);
	ft_putstr(prompt);
	return (ft_strlen(prompt));
}

char	*return_prompt(void)
{
	char	*prompt;
	t_loc	*local;

	local = get_loc("PS1");
	prompt = ft_strdup(local->value);
	prompt_management(&prompt);
	return (prompt);
}
