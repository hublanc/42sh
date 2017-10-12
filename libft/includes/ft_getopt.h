/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 11:20:16 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/08 10:24:27 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GETOPT_H
# define FT_GETOPT_H

# include <unistd.h>

extern char *g_optarg;
extern int g_optind;
extern int g_optopt;
extern int g_opterr;
extern int g_optreset;

int	ft_getopt(int ac, const char *av[], const char *optstring);

#endif
