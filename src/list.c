/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 15:09:13 by sblauens          #+#    #+#             */
/*   Updated: 2018/07/13 04:43:01 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			recursive_list(t_list *dir_files)
{
	while (dir_files)
	{
		if (ft_strcmp(((t_file *)(dir_files->content))->filename, ".")
				&& ft_strcmp(((t_file *)(dir_files->content))->filename, ".."))
		{
			if (S_ISDIR(((t_file *)(dir_files->content))->st_mode))
			{
				ft_putstr("\n");
				list_dir_content(((t_file *)(dir_files->content))->pathname);
			}
		}
		dir_files = dir_files->next;
	}
}

int					list_dir_content(char *dir_name)
{
	DIR					*dir_stream;
	t_list				*dir_files;

	dir_files = NULL;
	if (!(dir_stream = opendir(dir_name)))
		error_put(dir_name);
	else
	{
		get_dir_content(dir_name, dir_stream, &dir_files);
		if (closedir(dir_stream) == -1)
			error_put(dir_name);
		if (dir_files)
			ft_lstsort_merge(&dir_files, &cmp_files);
		print_dir(dir_name, dir_files);
		if (g_options.recursive)
			recursive_list(dir_files);
		if (dir_files)
			ft_lstdel(&dir_files, &del_file_node);
	}
	return (0);
}
