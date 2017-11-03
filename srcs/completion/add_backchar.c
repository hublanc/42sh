#include "shell.h"

char		*add_backchar(const char *name)
{
	char	*s;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (name[++i])
		if (name[i] == 32 || name[i] == '!')
			j++;
	if (!(s = (char *)ft_memalloc(ft_strlen(name) + j + 1)))
		return (NULL);
	ft_strcat(s, name);
	i = -1;
	while (s[++i])
		if (s[i] == 32 || s[i] == '!')
			saddchr(&s, '\\', i++);
	return (s);
}
