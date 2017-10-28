/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:46:11 by nbouchin          #+#    #+#             */
/*   Updated: 2017/10/25 14:46:10 by amazurie         ###   ########.fr       */
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

size_t	strlen_prompt(char *prompt)
{
	int		i;
	size_t	size;
	int		in_escape;

	if (!isatty(2))
		return (0);
	i = 0;
	in_escape = 0;
	size = 0;
	while (prompt[i])
	{
		if (prompt[i] == 27)
			in_escape = 1;
		else if ((in_escape == 1 && prompt[i] != '[')
				|| (in_escape == 2 && ft_isalpha(prompt[i])))
			in_escape = 0;
		else if (in_escape && prompt[i] == '[')
			in_escape = 2;
		else if (!in_escape)
			size++;
		i++;
	}
	return (size);
}

void	print_prompt(void)
{
	char	*prompt;
	char	*tmp;
	t_loc	*local;

	if (!isatty(0) || !isatty(2))
		return ;
	tmp = NULL;
	if (!(local = get_loc("PS1")))
	{
		if (!(tmp = get_elem(save_env(NULL), "PS1=")))
		{
			add_loc("PS1", "\e[36m\\u\e[32m@ \\W\e[0m\\$ > ");
			local = get_loc("PS1");
		}
	}
	(!tmp && local && local->value) ? tmp = local->value : 0;
	prompt = (tmp) ? ft_strdup(tmp) : ft_strdup("42sh> ");
	prompt_management(&prompt);
	ft_putstr_fd(prompt, 2);
	ft_strdel(&prompt);
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
			add_loc("PS1", "\e[36m\\u\e[32m@ \\W\e[0m\\$ > ");
			local = get_loc("PS1");
		}
	}
	(!tmp && local && local->value) ? tmp = local->value : 0;
	prompt = (tmp) ? ft_strdup(tmp) : ft_strdup("42sh> ");
	prompt_management(&prompt);
	return (prompt);
}
