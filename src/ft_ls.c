/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 11:59:22 by sblauens          #+#    #+#             */
/*   Updated: 2018/04/28 16:01:02 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				main(int ac, char **av)
{
	t_list		*working_dir_files;

	working_dir_files = NULL;
	if (ac > 1)
		get_dir_content(*(av + 1), &working_dir_files);
	else
		get_dir_content(".", &working_dir_files);
	del_recursive_list(&working_dir_files);
	return (0);
}
