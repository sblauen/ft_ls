/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   longlist_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 01:49:51 by sblauens          #+#    #+#             */
/*   Updated: 2018/08/07 23:38:46 by sblauens         ###   ########.fr       */
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

static inline size_t	nbr_align(char *buf, int n, size_t sp)
{
	register size_t		len;
	register int		k;

	k = 10;
	buf[sp] = 0;
	len = sp;
	if (!n)
		buf[--sp] = '0';
	else
	{
		while (n)
		{
			buf[--sp] = n % 10 + '0';
			n /= 10;
		}
	}
	while (sp > 0)
		buf[--sp] = ' ';
	return (len);
}

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

static inline char		*longlist_buf(t_file *file, t_sizes *sp)
{
	char				*buf;
	size_t				len;

	len = 12 + sp->nlink + sp->uid + sp->gid + 5
			+ sp->mjr + sp->size + 2 + 14 + ft_strlen(file->filename) + 1;
	if (!(buf = ft_strnew(len)))
		return (NULL);
	longlist_modes(file, buf);
	len = nbr_align(buf + 12, file->st_nlink, sp->nlink) + 12;
	len += longlist_id(file, sp, buf + len);
	if (sp->mjr)
	{
		if (S_ISCHR(file->st_mode) || S_ISBLK(file->st_mode))
		{
			len += nbr_align(buf + len, (file->st_rdev >> MAJOR) & 0xff, sp->mjr);
			len += ft_strlcpy(buf + len, ", ", 3);
			len += nbr_align(buf + len, file->st_rdev & 0xff, sp->size);
		}
		else
			len += nbr_align(buf + len, file->st_size, sp->mjr + sp->size + 2);
	}
	else
		len += nbr_align(buf + len, file->st_size, sp->size);
	len += ft_strlcpy(buf + len, ctime(&(file->mtime.tv_sec)) + 3, 14) - 9;
	len += ft_strlcpy(buf + len, " ", 2);
	ft_strcpy(buf + len, file->filename);
	return (buf);
}

void					longlist_print(t_list *files)
{
	char				*buf;
	char				tot[18];
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
		ft_strcpy(tot, "total ");
		nbr_align(tot + 6, sizes.blocks ,ft_nbrdgts(sizes.blocks));
		ft_putendl(tot);
	}
	while (tmp)
	{
		buf = longlist_buf(((t_file *)(tmp->content)), &sizes);
		ft_putendl(buf);
		ft_memdel((void **)&buf);
		tmp = tmp->next;
	}
}
