/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 11:59:22 by sblauens          #+#    #+#             */
/*   Updated: 2018/05/01 00:45:47 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				main(int ac, char **av)
{
	unsigned int	n;
	unsigned int	count;
	t_list			*cwd_files;
	t_options		options;

	n = 1;
	count = ac - 1;
	cwd_files = NULL;
	default_options(&options);
	if (ac > 1)
	{
		while (count)
		{
			--count;
			if (**(av + n) == '-')
				parse_option_args(*(av + n), &options);
			else
				break ;
			++n;
		}
	}
	if (*(av + n))
		list_dir_content(*(av + n), &cwd_files, &options);
	else
		list_dir_content(".", &cwd_files, &options);
	del_recursive_list(&cwd_files);
	return (0);
}
