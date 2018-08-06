/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 15:09:13 by sblauens          #+#    #+#             */
/*   Updated: 2018/08/07 00:45:11 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
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
**  Backup informations needed in long listing output.
*/
static inline void		longlist_stat(t_file *file_st, struct stat *statbuf)
{
	struct passwd		*pw;
	struct group		*gr;

	file_st->st_blocks = statbuf->st_blocks;
	file_st->st_nlink = statbuf->st_nlink;
	if ((pw = getpwuid(statbuf->st_uid)))
		file_st->pw_name = ft_strdup(pw->pw_name);
	else
		file_st->pw_name = ft_itoa(statbuf->st_uid);
	if ((gr = getgrgid(statbuf->st_gid)))
		file_st->gr_name = ft_strdup(gr->gr_name);
	else
		file_st->gr_name = ft_itoa(statbuf->st_gid);
	file_st->st_size = statbuf->st_size;
	file_st->st_rdev = statbuf->st_rdev;
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
		error_put(file_st);
		return (-1);
	}
	else
	{
		ft_strcpy(file_st->filename, file);
		file_st->st_mode = statbuf.st_mode;
		file_st->mtime.tv_sec = statbuf.st_mtim.tv_sec;
		file_st->mtime.tv_nsec = statbuf.st_mtim.tv_nsec;
		if (g_options.format == long_listing)
			longlist_stat(file_st, &statbuf);
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

int						get_content(t_file *dir, t_list **content)
{
	t_file				file_st;
	struct dirent		*dir_entry;
	DIR					*dir_stream;

	*content = NULL;
	if (!(dir_stream = opendir(dir->pathname)))
	{
		error_put(dir);
		return (-1);
	}
	else
	{
		while ((dir_entry = readdir(dir_stream)))
		{
			if (((g_options.dotfiles == none) && (*(dir_entry->d_name) != '.'))
					|| (g_options.dotfiles == all))
			{
				if (!cpy_stat(dir->pathname, dir_entry->d_name, &file_st))
					add_new_node(content, &file_st);
			}
		}
		if (closedir(dir_stream) == -1)
			error_put(dir);
	}
	return (0);
}
