/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   longlist_modes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 17:50:55 by sblauens          #+#    #+#             */
/*   Updated: 2018/08/12 03:56:41 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline void		longlist_filetype(t_file *file, char *buf)
{
	if (S_ISREG(file->st_mode))
		buf[0] = '-';
	else if (S_ISDIR(file->st_mode))
		buf[0] = 'd';
	else if (S_ISLNK(file->st_mode))
		buf[0] = 'l';
	else if (S_ISCHR(file->st_mode))
		buf[0] = 'c';
	else if (S_ISBLK(file->st_mode))
		buf[0] = 'l';
	else if (S_ISFIFO(file->st_mode))
		buf[0] = 'p';
	else if (S_ISSOCK(file->st_mode))
		buf[0] = 's';
}

static inline void		longlist_usrperm(t_file *file, char *buf)
{
	if (S_IRUSR & file->st_mode)
		buf[1] = 'r';
	else
		buf[1] = '-';
	if (S_IWUSR & file->st_mode)
		buf[2] = 'w';
	else
		buf[2] = '-';
	if (S_IXUSR & file->st_mode)
		buf[3] = 'x';
	else
		buf[3] = '-';
}

static inline void		longlist_grpperm(t_file *file, char *buf)
{
	if (S_IRGRP & file->st_mode)
		buf[4] = 'r';
	else
		buf[4] = '-';
	if (S_IWGRP & file->st_mode)
		buf[5] = 'w';
	else
		buf[5] = '-';
	if (S_IXGRP & file->st_mode)
		buf[6] = 'x';
	else
		buf[6] = '-';
}

static inline void		longlist_othperm(t_file *file, char *buf)
{
	if (S_IROTH & file->st_mode)
		buf[7] = 'r';
	else
		buf[7] = '-';
	if (S_IWOTH & file->st_mode)
		buf[8] = 'w';
	else
		buf[8] = '-';
	if (!(S_IXOTH & file->st_mode) && !(S_ISVTX & file->st_mode))
		buf[9] = '-';
	else if (S_IXOTH & file->st_mode)
		if (!(S_ISVTX & file->st_mode))
			buf[9] = 'x';
		else
			buf[9] = 't';
	else
		buf[9] = 'T';
}

void					longlist_modes(t_file *file, char *buf)
{
	longlist_filetype(file, buf);
	longlist_usrperm(file, buf);
	longlist_grpperm(file, buf);
	longlist_othperm(file, buf);
	strcpy(buf + 10, "  ");
}
