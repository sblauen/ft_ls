/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 19:38:36 by sblauens          #+#    #+#             */
/*   Updated: 2018/04/30 00:03:22 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				default_options(t_options *options)
{
	options->dotfiles = none;
	options->format = column;
	options->recursive = 0;
	options->reverse = 0;
	options->sort = name;
}

void				parse_option_args(char *arguments, t_options *options)
{
	while (*arguments)
	{
		if (*arguments == 'a')
			options->dotfiles = all;
		if (*arguments == 'l')
			options->format = long_listing;
		else if (*arguments == 'C')
			options->format = column;
		if (*arguments == 'R')
			options->recursive = 1;
		if (*arguments == 'r')
			options->reverse = 1;
		if (*arguments == 't')
			options->sort = time;
		++arguments;
	}
}
