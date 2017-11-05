/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 19:55:32 by lbopp             #+#    #+#             */
/*   Updated: 2016/11/08 21:03:10 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *big, const char *little)
{
	char	*debut;
	char	*substr;

	if (!*little)
		return ((char*)big);
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
			return (debut);
		big = debut + 1;
	}
	return (0);
}
