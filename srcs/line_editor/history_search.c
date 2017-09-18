/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:09:47 by mameyer           #+#    #+#             */
/*   Updated: 2017/09/18 15:09:49 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			history_search(t_hist **history, t_cmd *cmd, char ***env)
{
	t_cmd		research;

	research = init_cmd("bck-i-search: ");
	history_search_core(cmd, &research, history, env);
}

void			history_search_core(t_cmd *cmd, t_cmd *search, t_hist **history, char ***env)
{
	char		buf[3];
	t_hist		*tmp;

	(void)env;
	(void)history;
	(void)cmd;
	bzero(buf, 3);
	ft_putchar('\n');
	ft_putstr(search->prompt);
	tputs(tgetstr("us", NULL), 1, tputchar);
	ft_putchar(' ');
	tputs(tgetstr("ue", NULL), 1, tputchar);
	while (read(0, buf, 3))
	{
		if (buf[0] == 10)
		{
			ft_putstr("entering hub");
			return ;
		}
		else if (ft_isprint(buf[0]))
		{
			search->str = ft_strappone(search->str, buf[0], (search->col - 1) - search->prlen);
			search->sc_col++;
			tmp = *history;
			while (tmp != NULL)
			{
				if (tmp->cmd && search->str && ft_strstr(tmp->cmd, search->str) != NULL)
				{
					ft_strclr(cmd->str);
					cmd->str = ft_strdup(tmp->cmd);
				}
				tmp = tmp->next;
			}
			print_hist_research(cmd, search);
			go_right(search);
		}
		else if (buf[0] == 127 && search->col > search->prlen + 1)
		{
			search->str = ft_strdelone(search->str, (search->col - 1) - search->prlen);
			print_hist_research(cmd, search);
			go_left(search);
		}
	}
}

void			print_hist_research(t_cmd *cmd, t_cmd *search)
{
	tputs(tgetstr("rc", NULL), 1, tputchar);
	tputs(tgetstr("cd", NULL), 1, tputchar);
//	ft_putstr(cmd->prompt);
	ft_putendl(cmd->str);
	ft_putchar('\n');
	ft_putstr(search->prompt);
	ft_putstr(search->str);
	tputs(tgetstr("us", NULL), 1, tputchar);
	ft_putchar(' ');
	tputs(tgetstr("ue", NULL), 1, tputchar);
}

char			*new_strstr(const char *big, const char *little)
{
	size_t  i;
	size_t  j;
	size_t	k;

	i = 0;
	j = 0;
	if (!(*little))
		return ((char *)big);
	while (big[i] != '\0')
	{
		while (big[i + j] == little[j])
		{
			j++;
			if (j == ft_strlen(little))
			{
				k = 0;
				while (big[k] && k < i)
				{
					ft_putchar(big[k]);
					k++;
				}
				tputs(tgetstr("us", NULL), 1, tputchar);
				while (big[k] && k < ft_strlen(little))
				{
					ft_putchar(big[k]);
					k++;
				}
				tputs(tgetstr("ue", NULL), 1, tputchar);
				while (big[k])
				{
					ft_putchar(big[k]);
					k++;
				}
				return ((char *)&big[i]);
			}
		}
		i++;
		j = 0;
	}
	return (NULL);
}