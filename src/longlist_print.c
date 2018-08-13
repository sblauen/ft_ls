/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   longlist_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 01:49:51 by sblauens          #+#    #+#             */
/*   Updated: 2018/08/13 21:59:00 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline size_t		longlist_id(t_file *file, t_sizes *sp, char *buf)
{
	size_t				pw_len;
	size_t				gr_len;
	size_t				len;
	size_t				n;

	*buf = ' ';
	len = 1;
	pw_len = ft_strlen(file->pw_name);
	gr_len = ft_strlen(file->gr_name);
	len += ft_strlcpy(buf + 1, file->pw_name, pw_len + 1);
	n = sp->uid - pw_len + 2;
	while (n-- > 0)
		buf[len++] = ' ';
	len += ft_strlcpy(buf + len, file->gr_name, gr_len + 1);
	n = sp->gid - gr_len + 2;
	while (n-- > 0)
		buf[len++] = ' ';
	return (len);
}

static inline size_t	longlist_time(t_file *file, char *buf)
{
	size_t				len;
	time_t				six_m;
	char				*c_time;

	six_m = time(NULL) - ((time_t)SIXMONTHS);
	c_time = ctime(&(file->mtime.tv_sec));
	if (file->mtime.tv_sec < six_m)
	{
		len = ft_strlcpy(buf, c_time + 3, 9) - 14;
		len += ft_strlcpy(buf + len, c_time + 19, 6) - 1;
	}
	else
	{
		len = ft_strlcpy(buf, c_time + 3, 14) - 9;
	}
	return (len);
}

static inline void		longlist_lnk(t_file *file, char *buf)
{
	size_t				len;

	ft_strcpy(buf, " -> ");
	if ((len = readlink(file->pathname, buf + 4, 128)) > 0)
	{
		*(buf + len + 4) = 0;
	}
}

void					longlist_buf(t_file *file, t_sizes *sp, char *buf)
{
	size_t				len;

	longlist_modes(file, buf);
	len = nbr_align(buf + 12, file->st_nlink, sp->nlink) + 12;
	len += longlist_id(file, sp, buf + len);
	if (sp->mjr)
	{
		if (S_ISCHR(file->st_mode) || S_ISBLK(file->st_mode))
		{
			len += nbr_align(buf
					+ len, (file->st_rdev >> MAJOR) & 0xff, sp->mjr);
			len += ft_strlcpy(buf + len, ", ", 3);
			len += nbr_align(buf + len, file->st_rdev & 0xff, sp->size);
		}
		else
			len += nbr_align(buf + len, file->st_size, sp->mjr + sp->size + 2);
	}
	else
		len += nbr_align(buf + len, file->st_size, sp->size);
	len += longlist_time(file, buf + len);
	len += ft_strlcpy(buf + len, " ", 2);
	len += ft_strlcpy(buf + len, file->filename, sp->name + 1);
	if (S_ISLNK(file->st_mode))
		longlist_lnk(file, buf + len);
}
