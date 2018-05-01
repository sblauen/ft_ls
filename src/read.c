/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 15:09:13 by sblauens          #+#    #+#             */
/*   Updated: 2018/05/01 16:11:09 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern t_options	g_options;

int					get_dir_content(char *dir_name, DIR *dir_stream,
									t_list **dir_files)
{
	t_file				file;
	t_list				*node;
	struct dirent		*dir_entry;

	while ((dir_entry = readdir(dir_stream)))
	{
		if (((g_options.dotfiles == none) && (*(dir_entry->d_name) != '.'))
				|| (g_options.dotfiles == all))
		{
			ft_strcpy(file.pathname, dir_name);
			ft_strcat(file.pathname, "/");
			ft_strcat(file.pathname, dir_entry->d_name);
			ft_strcpy(file.filename, dir_entry->d_name);
			if (!(node = ft_lstnew(&file, sizeof(file))))
				return (-1);
			if (!*dir_files)
				*dir_files = node;
			else
				ft_lstadd_bck(dir_files, node);
		}
	}
	return (0);
}
