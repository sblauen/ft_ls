/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 15:09:13 by sblauens          #+#    #+#             */
/*   Updated: 2018/09/15 17:08:45 by sblauens         ###   ########.fr       */
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
	file_st->st_rdev = statbuf->st_rdev;
}

static inline void		cpy_time(t_file *file_st, struct stat *statbuf)
{
	if (g_options.time != modif_time)
	{
		if (g_options.time == access_time)
		{
			file_st->time.tv_sec = statbuf->st_atimespec.tv_sec;
			file_st->time.tv_nsec = statbuf->st_atimespec.tv_nsec;
		}
		else if (g_options.time == change_time)
		{
			file_st->time.tv_sec = statbuf->st_ctimespec.tv_sec;
			file_st->time.tv_nsec = statbuf->st_ctimespec.tv_nsec;
		}
	}
	else
	{
		file_st->time.tv_sec = statbuf->st_mtimespec.tv_sec;
		file_st->time.tv_nsec = statbuf->st_mtimespec.tv_nsec;
	}
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
	file_st->filename = ft_strdup(file);
	if (lstat(file_st->pathname, &statbuf))
	{
		return (error_file(file_st));
	}
	file_st->st_mode = statbuf.st_mode;
	file_st->st_size = statbuf.st_size;
	cpy_time(file_st, &statbuf);
	if (g_options.format == long_listing)
	{
		longlist_stat(file_st, &statbuf);
	}
	return (0);
}

/*
**  Retrieve the content of the directory 'dir_name' using the directory
**  entries in the directory stream.
*/

int						get_content(t_file *dir, t_list **content)
{
	int					ret;
	t_file				file_st;
	struct dirent		*dirent;
	DIR					*dir_stream;

	ret = 0;
	*content = NULL;
	if (!(dir_stream = opendir(dir->pathname)))
	{
		return (error_file(dir));
	}
	while ((dirent = readdir(dir_stream)))
	{
		if (((g_options.dotfiles == none) && (*(dirent->d_name) != '.'))
				|| (g_options.dotfiles == all))
			if (!(ret = cpy_stat(dir->pathname, dirent->d_name, &file_st)))
				add_new_node(content, &file_st);
	}
	if (closedir(dir_stream) == -1)
	{
		ret = error_file(dir);
	}
	return (ret);
}
