#include "shell.h"

//attention aucune des fonctions n'est tester
//ignore les caractere speciaux type '\' '!' '"'

//celle la rm tout de la fin jusqu'a trouver un '/' (si a pas fait rien)
void	rmpathname(char **arg)
{
	int		i;

	if (!arg || !*arg)
		return ;
	i = ft_strlen(*arg) - 1;
	if (i < 0 || !ft_strchr(*arg, '/'))
		return ;
	while ((*arg)[i] != '/')
		ssupprchr(arg, i--);
	(*arg)[i] == '/' ? ssupprchr(arg, i) : 0;
}

//celle la rm tout du debut de la command jusqu'a un '/' (pareil si a pas fait rien)
void	rmpathcomp(char **arg)
{
	if (!arg || !*arg)
		return ;
	while (ft_strchr(*arg + 1, '/'))
		ssupprchr(arg, 0);
	ssupprchr(arg, 0);
}

//tout de la fin jusqu'a un '.'
void	rmsuffix(char **arg)
{
	int		i;

	if (!arg || !*arg)
		return ;
	i = ft_strlen(*arg) - 1;
	if (i < 0 || !ft_strchr(*arg, '.'))
		return ;
	while ((*arg)[i] != '.')
		ssupprchr(arg, i--);
	(*arg)[i] == '.' ? ssupprchr(arg, i) : 0;
}

//debut > '.'
void	rmallbutsuffix(char **arg)
{
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
		return (NULL);
	i = ft_strlen(arg) + 3;
	if (!(s = (char *)ft_memalloc(sizeof(char) + i)))
		return (NULL);
	s[0] = '\'';
	ft_strcat(s, arg);
	ft_strcat(s, "'");
	return (s);
}

//quote chaque mot separer par un espace
char	*quoteword(char *arg)
{
	char	*s;
	int		i;
	int		j;
	int		k;

	if (!arg)
		return (NULL);
	i = -1;
	j = 0;
	while (arg[++i])
	{
		if (arg[i] == ' ' && (i <= 0 || arg[i - 1] == ' '))
			j += arg[i + 1] ? 3 : 2;
		else if (arg[i] != ' ')
			j += 2;
	}
	if (!(s = (char *)ft_memalloc(sizeof(char) + i + j + 1)))
		return (NULL);
	i = -1;
	k = ft_strlen(arg) - 1;
	while (++i < k)
	{
		if (arg[i] == ' ' && (i <= 0 || arg[i - 1] == ' '))
			arg[i + 1] ? ft_strcat(s, "'' ") : ft_strcat(s, "''");
		else if (arg[i] != ' ' && (j = ft_strlen_chr(arg + i, ' ')))
		{
			ft_strcat(s, "'");
			ft_strncat(s, arg + i, j);
			ft_strcat(s, "'");
			arg[i + 1] ? ft_strcat(s, " ") : 0;
			i += j;
		}
	}
	return (s);
}

//remplace dans la premiere chaine la premiere occcurence de old
//par new, toute les occurence si rec est positif
char	*modif_substi(char *arg, char *old, char *new, int rec)
{
	char	*s;
	int		i;
	int		j;
	int		k;
	int		l;

	if (!arg || !old || !new)
		return (NULL);
	i = -1;
	j = 0;
	while (new[++i] && (j == 0 || rec > 0))
		if (new[i] == '&' && (i <= 0 || new[i - 1] != '\\'))
			j++;
	i = 0;
	j *= ft_strlen(old);
	l = ft_strlen(arg);
	while ((i == 0 || rec > 0) && i < l
			&& (i = ft_strstr_len(arg + i, old)))
	{
		i += ft_strlen(old);
		j++;
	}
	if (!(s = (char *)ft_memalloc(sizeof(char) + i - (j * ft_strlen(old))
						 + (j * ft_strlen(new)) + 1)))
		return (NULL);
	i = 0;
	j = 0;
	l = ft_strlen(arg);
	while ((i == 0 || rec > 0) && i < l
			&& (i = ft_strstr_len(arg + i, old)))
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
