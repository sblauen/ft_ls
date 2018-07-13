/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 15:09:13 by sblauens          #+#    #+#             */
/*   Updated: 2018/07/14 02:38:44 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**  Copy the pathname of the file 'file' in the string pointed to by 'path'.
*/
static inline void		cpy_path(char *parent, char *file, char *path)
{
	register size_t		len;

	len = ft_strlen(parent) - 1;
	ft_strcpy(path, parent);
	if (*(parent + len) != '/')
		ft_strcat(path, "/");
	ft_strcat(path, file);
}

/*
**  Backup informations about the file 'file' in the buffer pointed to
**  by 'file_st'.
**
**  If an error occurs, a message using errno is written to standard error.
*/
static inline int		cpy_stat(char *parent, char *file, t_file *file_st)
{
	struct stat			statbuf;

	cpy_path(parent, file, file_st->pathname);
	if (lstat(file_st->pathname, &statbuf))
	{
		error_put(file_st->pathname);
		return (-1);
	}
	else
	{
		ft_strcpy(file_st->filename, file);
		file_st->st_mode = statbuf.st_mode;
		file_st->mtime.tv_sec = statbuf.st_mtim.tv_sec;
		file_st->mtime.tv_nsec = statbuf.st_mtim.tv_nsec;
		return (0);
	}
}

/*
**  Retrieve the content of the directory 'dir_name' using the directory
**  entries in the directory stream pointed to by 'dir_stream'.
*/
t_list					*get_content(char *dir_name, DIR *dir_stream)
{
	t_file				file_st;
	t_list				*node;
	t_list				*content;
	struct dirent		*dir_entry;

	content = NULL;
	while ((dir_entry = readdir(dir_stream)))
	{
		if (((g_options.dotfiles == none) && (*(dir_entry->d_name) != '.'))
				|| (g_options.dotfiles == all))
		{
			if (!cpy_stat(dir_name, dir_entry->d_name, &file_st))
			{
				if (!(node = ft_lstnew(&file_st, sizeof(file_st))))
					return (NULL);
				if (!content)
					content = node;
				else
					ft_lstadd_bck(&content, node);
			}
		}
	}
	return (content);
}
