/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 15:09:13 by sblauens          #+#    #+#             */
/*   Updated: 2018/07/29 20:25:12 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**  Copy the pathname of the file 'file' in the string pointed to by 'path'.
*/
static inline char		*cpy_path(char *parent, char *file)
{
	char				*path;
	register size_t		len_path;
	register size_t		len_file;

	len_path = ft_strlen(parent);
	len_file = ft_strlen(file);
	if (*(parent + len_path - 1) != '/')
		++len_file;
	if (!(path = (char *)malloc(sizeof(char) * (len_path + len_file) + 1)))
		return (NULL);
	ft_strcpy(path, parent);
	if (*(parent + len_path - 1) != '/')
		ft_strcat(path, "/");
	ft_strcat(path, file);
	return (path);
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

	file_st->pathname = cpy_path(parent, file);
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
		file_st->st_nlink = statbuf.st_nlink;
		file_st->st_uid = statbuf.st_uid;
		file_st->st_gid = statbuf.st_gid;
		file_st->st_size = statbuf.st_size;
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
