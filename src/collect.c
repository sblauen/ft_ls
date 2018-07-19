/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 15:09:13 by sblauens          #+#    #+#             */
/*   Updated: 2018/07/19 18:15:03 by sblauens         ###   ########.fr       */
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
**  Make a new node containing the data of 'file_st' and add it to
**  the list pointed to by '*content'.
*/
static inline void		add_new_node(t_list **content, t_file *file_st)
{
	t_list				*node;

	if (!(node = ft_lstnew(file_st, sizeof(*file_st))))
		return ;
	if (!*content)
		*content = node;
	else
		ft_lstadd_bck(content, node);
}

/*
**  Retrieve the content of the directory 'dir_name' using the directory
**  entries in the directory stream.
*/
int						get_content(char *dir_name, t_list **content)
{
	t_file				file_st;
	struct dirent		*dir_entry;
	DIR					*dir_stream;

	*content = NULL;
	if (!(dir_stream = opendir(dir_name)))
	{
		error_put(dir_name);
		return (-1);
	}
	else
	{
		while ((dir_entry = readdir(dir_stream)))
		{
			if (((g_options.dotfiles == none) && (*(dir_entry->d_name) != '.'))
					|| (g_options.dotfiles == all))
			{
				if (!cpy_stat(dir_name, dir_entry->d_name, &file_st))
					add_new_node(content, &file_st);
			}
		}
		if (closedir(dir_stream) == -1)
			error_put(dir_name);
	}
	return (0);
}
