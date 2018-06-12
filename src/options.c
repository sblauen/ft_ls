/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 19:38:36 by sblauens          #+#    #+#             */
/*   Updated: 2018/06/12 17:02:28 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern t_options				g_options;

static inline void				default_options()
{
	g_options.dotfiles = none;
	g_options.format = column;
	g_options.recursive = 0;
	g_options.reverse = 0;
	g_options.sort = name;
	g_options.multi_files = 0;
}

static inline void				parse_option_args(char *arguments)
{
	while (*arguments)
	{
		if (*arguments == 'a')
			g_options.dotfiles = all;
		if (*arguments == 'l')
			g_options.format = long_listing;
		else if (*arguments == 'C')
			g_options.format = column;
		if (*arguments == 'R')
			g_options.recursive = 1;
		if (*arguments == 'r')
			g_options.reverse = 1;
		if (*arguments == 't')
			g_options.sort = time;
		++arguments;
	}
}

void							check_options(int ac, char **av, int *n)
{
	default_options();
	while (*(av + *n))
	{
		if (**(av + *n) == '-')
			parse_option_args(*(av + *n) + 1);
		else
			break ;
		++(*n);
	}
	if (ac - *n > 1 || g_options.recursive)
		g_options.multi_files = 1;
}
