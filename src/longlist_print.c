/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   longlist_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 01:49:51 by sblauens          #+#    #+#             */
/*   Updated: 2018/08/06 20:15:30 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline void		get_sizes(t_list *files, t_sizes *sizes)
{
	t_sizes				ret;
	t_file				*file;

	while (files)
	{
		file = (t_file *)(files->content);
		sizes->blocks += file->st_blocks;
		if ((ret.nlink = ft_nbrdgts(file->st_nlink)) > sizes->nlink)
			sizes->nlink = ret.nlink;
		if ((ret.uid = ft_strlen(file->pw_name)) > sizes->uid)
			sizes->uid = ret.uid;
		if ((ret.gid = ft_strlen(file->gr_name)) > sizes->gid)
			sizes->gid = ret.gid;
		if (S_ISCHR(file->st_mode) || S_ISBLK(file->st_mode))
		{
			if ((ret.mjr = ft_nbrdgts((file->st_rdev >> MAJOR) & 0xff))
				> sizes->mjr)
				sizes->mjr = ret.mjr;
			if ((ret.size = ft_nbrdgts(file->st_rdev & 0xff)) > sizes->size)
				sizes->size = ret.size;
		}
		else if ((ret.size = ft_nbrdgts(file->st_size)) > sizes->size)
			sizes->size = ret.size;
		files = files->next;
	}
}

static inline char		*nbr_align(int n, size_t sp)
{
	static char			buf[11];
	register int		k;

	k = 10;
	buf[10] = 0;
	if (!n)
		buf[--k] = '0';
	else
	{
		while (n)
		{
			buf[--k] = n % 10 + '0';
			n /= 10;
		}
	}
	n = (int)(sp - 10 + k);
	while (n-- > 0)
		buf[--k] = ' ';
	return (buf + k);
}

static inline char		*longlist_uid_gid(t_file *file, t_sizes *spaces)
{
	char				*buf;
	size_t				pw_len;
	size_t				gr_len;

	pw_len = ft_strlen(file->pw_name);
	gr_len = ft_strlen(file->gr_name);
	if (!(buf = (char *)malloc(sizeof(char) * (spaces->uid + spaces->gid) + 6)))
		return (NULL);
	*buf = ' ';
	ft_strcpy(buf + 1, file->pw_name);
	ft_strncat_chr(buf + pw_len + 1, ' ', spaces->uid - pw_len + 2);
	ft_strcat(buf, file->gr_name);
	ft_strncat_chr(buf + gr_len + 1, ' ', spaces->gid - gr_len + 2);
	return (buf);
}

static inline char		*longlist_buf(t_file *file, t_sizes *spaces)
{
	char				*buf;
	char				*tmp;
	size_t				len;

	len = 12 + spaces->nlink + spaces->uid + spaces->gid + 5
			+ spaces->mjr + spaces->size + 2 + 14 + ft_strlen(file->filename) + 1;
	if (!(buf = ft_strnew(len)))
		return (NULL);
	longlist_modes(file, buf);
	len = ft_strlcpy(buf + 12, nbr_align(file->st_nlink, spaces->nlink), spaces->nlink + 1) + 12;
	tmp = longlist_uid_gid(file, spaces);
	len += ft_strlcpy(buf + len, tmp, ft_strlen(tmp) + 1);
	ft_memdel((void **)&tmp);
	if (spaces->mjr)
	{
		if (S_ISCHR(file->st_mode) || S_ISBLK(file->st_mode))
		{
			len += ft_strlcpy(buf + len, nbr_align((file->st_rdev >> MAJOR)
				& 0xff, spaces->mjr), spaces->mjr + 1);
			len += ft_strlcpy(buf + len, ", ", 3);
			len += ft_strlcpy(buf + len, nbr_align(file->st_rdev & 0xff,
						spaces->size), spaces->size + 1);
		}
		else
		{
			len += ft_strlcpy(buf + len,
				nbr_align(file->st_size, spaces->mjr + spaces->size + 2),
				spaces->size + spaces->mjr + 3);
		}
	}
	else
		len += ft_strlcpy(buf + len, nbr_align(file->st_size, spaces->size), spaces->size + 1);
	len += ft_strlcpy(buf + len, ctime(&(file->mtime.tv_sec)) + 3, 14);
	len -= 9;
	len += ft_strlcpy(buf + len, " ", 2);
	ft_strcpy(buf + len, file->filename);
	return (buf);
}

void					longlist_print(t_list *files)
{
	char				*buf;
	t_list				*tmp;
	t_sizes				sizes;

	tmp = files;
	if (tmp)
	{
		sizes.blocks = 0;
		sizes.nlink = 0;
		sizes.size = 0;
		sizes.uid = 0;
		sizes.gid = 0;
		sizes.mjr = 0;
		get_sizes(tmp, &sizes);
		ft_putstr("total ");
		ft_putnbr(sizes.blocks);
		ft_putchar('\n');
	}
	while (tmp)
	{
		buf = longlist_buf(((t_file *)(tmp->content)), &sizes);
		ft_putendl(buf);
		ft_memdel((void **)&buf);
		tmp = tmp->next;
	}
}
