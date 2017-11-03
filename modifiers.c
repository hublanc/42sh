#include "shell.h"

//j'ai test aucune fonction un truc a faire

//celle la rm tout de la fin jusqu'a trouver un '/' (si a pas fait rien)
void	rmpathname(char **arg)
{
	char	*s;
	int		i;

	if (!arg || !*arg)
		return ;
	i = ft_strlen(*arg) - 1;
	if (i < 0 || !ft_strchr(*arg, '/'))
		return ;
	while ((*arg)[i] != '/')
		ssupprchr(arg, i--);
	(*arg)[i] != '/' ? ssupprchr(arg, i) : 0;
}

//celle la rm tout du debut de la command jusqu'a un '/' (pareil si a pas fait rien)
void	rmpathcomp(char **arg)
{
	char	*s;
	int		i;

	if (!arg || !*arg)
		return ;
	while (ft_strchr(*arg + 1, '/'))
		ssupprchr(arg, 0);
}

//tout de la fin jusqu'a un '.'
void	rmsuffix(char **arg)
{
	char	*s;
	int		i;

	if (!arg || !*arg)
		return ;
	i = ft_strlen(*arg) - 1;
	if (i < 0 || !ft_strchr(*arg, '.'))
		return ;
	while ((*arg)[i] != '.')
		ssupprchr(arg, i--);
	(*arg)[i] != '.' ? ssupprchr(arg, i) : 0;
}

//debut > '.'
void	rmallbutsuffix(char **arg)
{
	char	*s;
	int		i;

	if (!arg || !*arg)
		return ;
	while (ft_strchr(*arg + 1, '.'))
		ssupprchr(arg, 0);
}

//well i wil not do 'p' :D

//celle du dessous je malloc et retourne un char
char	*quoteit(char *arg)
{
	char	*s;
	int		i;

	if (!arg)
		return (NULL);;
	i = ft_strlen(arg) + 3;
	if (!(s = (char *)ft_memalloc(sizeof(char) + i)))
		return (NULL);
	s[0] = '\'';
	ft_strcat(s, arg);
	s[i - 1] = '\'';
	return (s);
}

char	*quoteword(char *arg)
{
	char	*s;
	int		i;
	int		j;

	if (!arg)
		return (NULL);
	i = 0;
	j = 0;
	while (arg[i])
	{
		(arg[i] == ' ') ? j += 2 : 0;
		while (arg[i] == ' ')
			i++;
	}
	if (!(s = (char *)ft_memalloc(sizeof(char) + i + j + 1)))
		return (NULL);
	while (i < ft_strlen(arg))
	{
		while (arg[i] == ' ')
			i++;
		ft_strncat(s, arg, i);
		ft_strncat(s, "'", i);
		j = ft_strlen_chr(arg + i, ' ');
		ft_strncat(s, arg + i, j);
		ft_strncat(s, "'", i);
	}
}
