/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 15:34:42 by sblauens          #+#    #+#             */
/*   Updated: 2018/04/28 16:02:08 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			del_file_node(void *content, size_t size)
{
	(void)size;
	ft_memdel(&content);
}

void			del_recursive_list(t_list **dir_files)
{
	t_list		*tmp;
	t_list		*subdir_files;

	tmp = *dir_files;
	while (tmp)
	{
		if (((t_file *)(tmp->content))->subfiles)
		{
			subdir_files = ((t_file *)(tmp->content))->subfiles;
			del_recursive_list(&subdir_files);
		}
		tmp = tmp->next;
	}
	ft_lstdel(dir_files, &del_file_node);
}
