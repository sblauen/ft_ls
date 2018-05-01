/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 11:59:22 by sblauens          #+#    #+#             */
/*   Updated: 2018/05/01 16:10:40 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_options			g_options;

int					main(int ac, char **av)
{
	unsigned int	n;
	unsigned int	count;

	n = 1;
	count = ac - 1;
	default_options();
	if (ac > 1)
	{
		while (count)
		{
			--count;
			if (**(av + n) == '-')
				parse_option_args(*(av + n));
			else
				break ;
			++n;
		}
	}
	if (*(av + n))
		list_dir_content(*(av + n));
	else
		list_dir_content(".");
	return (0);
}
