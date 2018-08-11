/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   longlist_sizes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 16:17:54 by sblauens          #+#    #+#             */
/*   Updated: 2018/08/11 23:18:58 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline void		init_sizes(t_sizes *sizes)
{
		sizes->nlink = 0;
		sizes->name = 0;
		sizes->uid = 0;
		sizes->gid = 0;
		sizes->mjr = 0;
		sizes->size = 0;
		sizes->blocks = 0;
}

static inline void		spe_sizes(dev_t st_rdev, t_sizes *sizes, t_sizes *ret)
{
	if ((ret->mjr = ft_nbrdgts((st_rdev >> MAJOR) & 0xff)) > sizes->mjr)
		sizes->mjr = ret->mjr;
	if ((ret->size = ft_nbrdgts(st_rdev & 0xff)) > sizes->size)
		sizes->size = ret->size;
}

static inline void		get_sizes(t_list *files, t_sizes *sizes)
{
	t_sizes				ret;
	t_file				*file;

	while (files)
	{
		file = (t_file *)(files->content);
		sizes->blocks += file->st_blocks;
		if ((ret.name = ft_strlen(file->filename)) > sizes->name)
			sizes->name = ret.name;
		if ((ret.nlink = ft_nbrdgts(file->st_nlink)) > sizes->nlink)
			sizes->nlink = ret.nlink;
		if ((ret.uid = ft_strlen(file->pw_name)) > sizes->uid)
			sizes->uid = ret.uid;
		if ((ret.gid = ft_strlen(file->gr_name)) > sizes->gid)
			sizes->gid = ret.gid;
		if (S_ISCHR(file->st_mode) || S_ISBLK(file->st_mode))
			spe_sizes(file->st_rdev, sizes, &ret);
		else if ((ret.size = ft_nbrdgts(file->st_size)) > sizes->size)
			sizes->size = ret.size;
		files = files->next;
	}
}

void					longlist_sizes(t_list *files, t_sizes *sizes)
{
	init_sizes(sizes);
	get_sizes(files, sizes);
	sizes->len = 12 + sizes->nlink + sizes->uid + sizes->gid + 5 + 128
					+ sizes->mjr + sizes->size + sizes->name + 2 + 14 + 1;
}
