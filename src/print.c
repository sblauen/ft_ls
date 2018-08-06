/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:58:21 by sblauens          #+#    #+#             */
/*   Updated: 2018/08/06 21:42:10 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void					print_dir(t_list *dir_files)
{
	t_list				*tmp;

	tmp = dir_files;
	if (g_options.format == long_listing)
	{
		longlist_print(dir_files);
	}
	else
		while (tmp)
		{
			ft_putendl(((t_file *)(tmp->content))->filename);
			tmp = tmp->next;
		}
}
