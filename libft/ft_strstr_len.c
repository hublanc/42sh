/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 19:37:47 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/04 19:37:49 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strstr_len(const char *big, const char *little)
{
	char	*debut;
	char	*substr;
	int		len;

	if (!*little)
		return (0);
	len = 0;
	while (*big)
	{
		debut = (char*)big;
		substr = (char*)little;
		while (*big && *substr && *big == *substr)
		{
			substr++;
			big++;
		}
		if (!*substr)
			return (len);
		len++;
		big = debut + 1;
	}
	return (0);
}
