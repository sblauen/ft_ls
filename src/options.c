/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 19:38:36 by sblauens          #+#    #+#             */

/*   Updated: 2018/08/19 09:18:27 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_options				g_options;

static inline void		default_options(void)
{
	g_options.dotfiles = none;
	g_options.format = column;
	g_options.recursive = 0;
	g_options.reverse = 0;
	g_options.sort = name;
	g_options.time = modif_time;
	g_options.multi_files = 0;
}

static inline void		parse_option_args(char *arguments)
{
	while (*arguments)
	{
		if (!ft_strchr(OPTIONS, *arguments))
			error_options(*arguments);
		if (*arguments == 'a' || *arguments == 'f')
			g_options.dotfiles = all;
		if (*arguments == 'l')
			g_options.format = long_listing;
		if (*arguments == '1')
			g_options.format = one_per_line;
		if (*arguments == 'R')
			g_options.recursive = 1;
		if (*arguments == 'r')
			g_options.reverse = 1;
		if (*arguments == 't' && g_options.sort < by_time)
			g_options.sort = by_time;
		if (*arguments == 'S' && g_options.sort < by_size)
			g_options.sort = by_size;
		if (*arguments == 'f')
			g_options.sort = unsorted;
		if (*arguments == 'c')
			g_options.time = change_time;
		if (*arguments == 'u')
			g_options.time = access_time;
		++arguments;
	}
}

void					check_options(int ac, char **av, int *n)
{
	default_options();
	while (*(av + *n))
	{
		if (**(av + *n) == '-' && *(*(av + *n) + 1))
		{
			if (*(*(av + *n) + 1) == '-' && !*(*(av + *n) + 2))
			{
				++(*n);
				break ;
			}
			else
			{
				parse_option_args(*(av + *n) + 1);
			}
		}
		else
			break ;
		++(*n);
	}
	if (ac - *n > 1)
		g_options.multi_files = 1;
}
