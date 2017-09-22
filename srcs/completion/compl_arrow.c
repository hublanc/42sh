#include "shell.h"

int			compl_arrow(t_compl *compl, t_cmd *cmd, char *buf)
{
	if (compl || cmd || buf)
		;
/*	if (buf[2] == 68)
		gest_left(compl, cmd);
	else if (buf[2] == 67)
		gest_right(compl, cmd);
	else if (buf[2] == 65)
		compl->curr = (compl->curr > 0) ? compl->curr - 1 : compl->nbrargs - 1;
	else if (buf[2] == 66)
		compl->curr = (compl->curr < compl->nbrargs - 1) ? compl->curr + 1 : 0;
	else
		return (0);
*/	return (1);
}
