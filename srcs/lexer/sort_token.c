/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 15:40:59 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/20 17:47:02 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_token			*check_redirection(t_token *list,
				t_token **cur, t_control **history)
{
	t_token		*tmp;
	t_token		*prev;

	tmp = *cur;
	prev = get_prev(list, tmp);
	if (!tmp->next || tmp->next->e_type != WORD)
	{
		ft_putstr_fd("parse error near redir\n", 2);
		del_token(&list);
		return (list);
	}
	if (prev && prev->e_type == IO_NUMBER)
	{
		tmp->token = ft_strappone(tmp->token, *(prev->token), 0);
		list = destroy_one(list, prev);
	}
	tmp->token = ft_strapp(tmp->token, " ");
	if (!ft_strstr(tmp->token, "<<"))
		tmp->token = ft_strapp(tmp->token, tmp->next->token);
	else if (!prompt_heredoc(tmp->next->token, tmp, history))
		del_token(&list);
	(list) ? list = destroy_one(list, tmp->next) : 0;
	*cur = tmp->next;
	return (list);
}

t_token			*check_word(t_token *list, t_token **cur, t_control **history)
{
	t_token			*tmp;
	t_token			*next;

	tmp = *cur;
	next = tmp->next;
	while (next && (next->e_type == WORD || next->e_type == REDIRECTION
	|| next->e_type == IO_NUMBER))
	{
		if (next && next->e_type == REDIRECTION)
		{
			list = check_redirection(list, &next, history);
			if (!list)
				return (list);
		}
		else if (next && next->e_type == WORD)
			extra_check_word(list, tmp, &next);
		else
			next = next ? next->next : NULL;
	}
	*cur = next;
	return (list);
}

t_token			*check_pipe(t_token *list, t_token **cur)
{
	t_token		*tmp;
	t_token		*prev;

	tmp = *cur;
	prev = get_prev(list, tmp);
	if (tmp->next && (tmp->next->e_type == PIPE || tmp->next->e_type == OU))
		return (abort_sort(list, "'|'"));
	else if (tmp->next && tmp->next->e_type == SEMI_COLON)
		return (abort_sort(list, "';'"));
	else if (!prev)
		return (abort_sort(list, "'|'"));
	*cur = tmp->next;
	return (list);
}

t_token			*check_sc(t_token *list, t_token **cur)
{
	t_token		*tmp;
	t_token		*prev;

	tmp = *cur;
	prev = get_prev(list, tmp);
	if (!prev && tmp && tmp->e_type == ET)
		return (abort_sort(list, "'&&'"));
	if (!prev && tmp && tmp->e_type == OU)
		return (abort_sort(list, "'||'"));
	if (tmp->next && tmp->next->e_type == ET)
		return (abort_sort(list, "'&&'"));
	if (tmp->next && tmp->next->e_type == OU)
		return (abort_sort(list, "'||'"));
	if (tmp->next && tmp->next->e_type == SEMI_COLON)
		return (abort_sort(list, "';;'"));
	if (tmp->next && tmp->next->e_type == PIPE)
		return (abort_sort(list, "'|'"));
	*cur = tmp->next;
	return (list);
}

t_token			*sort_token(t_token *list, t_control **history)
{
	t_token		*tmp;

	tmp = list;
	while (tmp && list)
	{
		if (tmp->e_type == WORD)
			list = check_word(list, &tmp, history);
		else if (tmp->e_type == REDIRECTION)
			list = check_redirection(list, &tmp, history);
		else if (tmp->e_type == PIPE)
			list = check_pipe(list, &tmp);
		else if (tmp->e_type == SEMI_COLON || tmp->e_type == OU
				|| tmp->e_type == ET)
			list = check_sc(list, &tmp);
		else
			tmp = tmp->next;
	}
	return (list);
}
