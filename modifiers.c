#include "shell.h"

//attention aucune des fonctions n'est tester
//ignore les caractere speciaux type '\' '!' '"'

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

//quote chaque mot separer par un espace
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
	return (s);
}

char	*modif_substi(char *arg, char *old, char *new)
{
	char	*s;
	int		i;
	int		j;
	int		k;

	if (!arg || !old || !new)
		return (NULL);
	i = -1;
	j = 0;
	while (new[++i])
		if (new[i] == '&' && (i <= 0 || new[i - 1] != '\\'))
			j++;
	i = 0;
	j *= ft_strlen(old);
	while (i < ft_strlen(arg) && (i = ft_strstr_len(arg + i, old)))
	{
		i += ft_strlen(old);
		j++;
	}
	if (!(s = (char *)ft_memalloc(sizeof(char) + i - (j * ft_strlen(old))
						 + (j * ft_strlen(new)) + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_strlen(arg) && (i = ft_strstr_len(arg + i, old)))
	{
		ft_strncat(s, arg + j, i);
		j = i + ft_strlen(old);
		if (!ft_strchr(new, '&'))
			ft_strcat(s, new);
		else
		{
			k = 0;
			while (new[k])
			{
				if (new[k] == '&' && (k <= 0 || new[k - 1] == '\\'))
					ft_strcat(s, old);
				else
					s[ft_strlen(s)] = new[k];
			}
		}
	}
	ft_strncat(s, arg + j, i);
	return (s);
}
