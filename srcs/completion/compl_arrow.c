/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compl_arrow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 11:08:56 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/19 15:09:25 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	compl_endhome(t_compl *compl, t_cmd *cmd, char *buf)
{
	int	*size;

	size = get_size(compl, cmd);
	if ((buf[0] == 27 && buf[1] == 91 && (buf[2] == 72 || buf[2] == 70))
			|| ((buf[0] == 1 || buf[0] == 5) && !buf[1]))
	{
		size[6] = 0;
		if (buf[2] == 72 || buf[0] == 1)
		{
			while (compl->curr < size[4] * size[6]
					|| compl->curr > size[4] * size[6] + size[4])
				size[6]++;
			compl->curr = size[4] * size[6];
			free(size);
			return (1);
		}
		while (compl->curr < size[4] * size[6]
				|| compl->curr > size[4] * size[6] + size[4])
			size[6]++;
		compl->curr = size[4] * size[6] + --size[4];
		free(size);
		return (1);
	}
	free(size);
	return (0);
}

static void	hand_rlcompl(t_compl *compl, t_cmd *cmd, char *buf)
{
	int	*size;

	if ((buf[0] == 27 && buf[1] == 91 && buf[2] == 67 && !buf[3])
			|| (buf[0] == 2 && !buf[1]))
	{
		size = get_size(compl, cmd);
		if (compl->curr + size[4] > compl->nbrargs - 1 && ++compl->curr >= -1)
			while (compl->curr - size[4] >= 0)
				compl->curr -= size[4];
		else
			compl->curr += size[4];
		free(size);
	}
	else
	{
		size = get_size(compl, cmd);
		if (compl->curr - size[4] < 0 && --compl->curr >= -1)
			while (compl->curr + size[4] <= compl->nbrargs - 1)
				compl->curr += size[4];
		else
			compl->curr -= size[4];
		free(size);
	}
}

int			compl_arrow(t_compl *compl, t_cmd *cmd, char *buf)
{
	if ((buf[0] == 27 && buf[1] == 91 && ((buf[2] == 65 && !buf[3])
					|| (buf[2] == 53 && buf[3] == 126)))
			|| (buf[0] == 16 && !buf[1]))
		compl->curr = compl->curr - 1 < 0 ? compl->nbrargs - 1 :
			compl->curr - 1;
	else if ((buf[0] == 27 && buf[1] == 91 && ((buf[2] == 66 && !buf[3])
					|| (buf[2] == 54 && buf[3] == 126)))
			|| (buf[0] == 14 && !buf[1]))
		compl->curr = compl->curr + 1 > compl->nbrargs - 1 ? 0 :
			compl->curr + 1;
	else if (((buf[0] == 27 && buf[1] == 91 && buf[2] == 67 && !buf[3])
				|| (buf[0] == 2 && !buf[1])) ||
				((buf[0] == 27 && buf[1] == 91 && buf[2] == 68 && !buf[3])
				|| (buf[0] == 6 && !buf[1])))
		hand_rlcompl(compl, cmd, buf);
	else
		return (compl_endhome(compl, cmd, buf));
	return (1);
}
