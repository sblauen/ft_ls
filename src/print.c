/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:58:21 by sblauens          #+#    #+#             */
/*   Updated: 2018/08/05 13:53:38 by sblauens         ###   ########.fr       */
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

static inline void		longlist_uid_gid(t_file *file, t_sizes *spaces)
{
	char				*buf;
	size_t				pw_len;
	size_t				gr_len;

	pw_len = ft_strlen(file->pw_name);
	gr_len = ft_strlen(file->gr_name);
	if (!(buf = (char *)malloc(sizeof(char) * (spaces->uid + spaces->gid) + 6)))
		return ;
	*buf = ' ';
	ft_strcpy(buf + 1, file->pw_name);
	ft_strncat_chr(buf + pw_len + 1, ' ', spaces->uid - pw_len + 2);
	ft_strcat(buf, file->gr_name);
	ft_strncat_chr(buf + gr_len + 1, ' ', spaces->gid - gr_len + 2);
	ft_putstr(buf);
	ft_memdel((void **)&buf);
}

static inline void		print_longlist(t_file *file, t_sizes *spaces)
{
	char				buf_mode[13];
	char				buf_time[23];

	longlist_modes(file, buf_mode);
	ft_putstr(buf_mode);
	ft_putnbr_ralign(file->st_nlink, spaces->nlink);
	longlist_uid_gid(file, spaces);
	if (S_ISCHR(file->st_mode) || S_ISBLK(file->st_mode))
	{
		ft_putnbr_ralign((file->st_rdev >> MAJOR) & 0xff, spaces->mjr);
		ft_putstr(", ");
		ft_putnbr_ralign(file->st_rdev & 0xff, spaces->size);
	}
	else
		ft_putnbr_ralign(file->st_size, spaces->size);
	strcpy(buf_time, ctime(&(file->mtime.tv_sec)) + 3);
	strcpy(buf_time + 13, " ");
	ft_putstr(buf_time);
}

void					print_dir(char *dir_name, t_list *dir_files)
{
	t_list				*tmp;
	t_sizes				sizes;

	tmp = dir_files;
	dir_name = NULL;
	if (tmp && g_options.format == long_listing)
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
		if (g_options.format == long_listing)
			print_longlist(((t_file *)(tmp->content)), &sizes);
		ft_putendl(((t_file *)(tmp->content))->filename);
		tmp = tmp->next;
	}
}
