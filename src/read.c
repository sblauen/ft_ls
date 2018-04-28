/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 15:09:13 by sblauens          #+#    #+#             */
/*   Updated: 2018/04/28 16:20:09 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				error_exit(void)
{
	perror("ft_ls: ");
	exit(EXIT_FAILURE);

}

void				recursive_list(t_list *dir_files)
{
	t_list				*subdir_files;
	struct stat			statbuf;

	while (dir_files)
	{
		subdir_files = NULL;
		if (ft_strcmp(((t_file *)(dir_files->content))->filename, ".")
				&& ft_strcmp(((t_file *)(dir_files->content))->filename, ".."))
		{
			if (stat(((t_file *)(dir_files->content))->pathname, &statbuf))
				error_exit();
			if (S_ISDIR(statbuf.st_mode))
				get_dir_content(((t_file *)(dir_files->content))->pathname,
						&subdir_files);
		}
		((t_file *)(dir_files->content))->subfiles = subdir_files;
		dir_files = dir_files->next;
	}
}

int					get_dir_content(char *dir_name, t_list **dir_files)
{
	t_file				file;
	t_list				*node;
	DIR					*dir_stream;
	struct dirent		*dir_entry;

	errno = 0;
	if (!(dir_stream = opendir(dir_name)))
		error_exit();
	while ((dir_entry = readdir(dir_stream)))
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
	print_dir_content(*dir_files);
	recursive_list(*dir_files);
	if (closedir(dir_stream) == -1)
		error_exit();
	return (0);
}
