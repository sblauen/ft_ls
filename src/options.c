/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 19:38:36 by sblauens          #+#    #+#             */
/*   Updated: 2018/05/01 16:09:33 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern t_options	g_options;

void				default_options()
{
	g_options.dotfiles = none;
	g_options.format = column;
	g_options.recursive = 0;
	g_options.reverse = 0;
	g_options.sort = name;
}

void				parse_option_args(char *arguments)
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
