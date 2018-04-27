/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 11:59:22 by sblauens          #+#    #+#             */
/*   Updated: 2018/04/27 15:12:57 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			del_file_node(void *content, size_t size)
{
	(void)size;
	ft_memdel(&content);
}

void			print_dir_content(t_list **dir_files)
{
	t_list		*tmp;
	t_list		*subdir_files;

	tmp = *dir_files;
	while (tmp)
	{
		ft_putendl(((t_file *)(tmp->content))->pathname);
		tmp = tmp->next;
	}
	tmp = *dir_files;
	subdir_files = NULL;
	while (tmp)
	{
		if (ft_strcmp(((t_file *)(tmp->content))->filename, ".")
				&& ft_strcmp(((t_file *)(tmp->content))->filename, ".."))
		{
			if (((t_file*)(tmp->content))->subfiles)
			{
				subdir_files = (((t_file*)(tmp->content))->subfiles);
				print_dir_content(&subdir_files);
			}
		}
		tmp = tmp->next;
	}
	ft_lstdel(dir_files, &del_file_node);
}

int				main(int ac, char **av)
{
	t_list		*working_dir_files;

	working_dir_files = NULL;
	if (ac > 1)
		get_dir_content(*(av + 1), &working_dir_files);
	else
		get_dir_content(".", &working_dir_files);
	print_dir_content(&working_dir_files);
	return (0);
}
