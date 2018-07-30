/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:58:21 by sblauens          #+#    #+#             */
/*   Updated: 2018/07/30 02:44:08 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
#include "ft_ls.h"

static inline t_sizes	get_sizes(t_list *files)
{
	size_t				ret_nlink;
	size_t				ret_size;
	t_sizes				sizes;

	sizes.nlink = 0;
	sizes.size = 0;
	sizes.blocks = 0;
	while (files)
	{
		sizes.blocks += ((t_file *)(files->content))->st_blocks;
		ret_nlink = ft_nbrpwr(((t_file *)(files->content))->st_nlink);
		if (ret_nlink > sizes.nlink)
			sizes.nlink = ret_nlink;
		ret_size = ft_nbrpwr(((t_file *)(files->content))->st_size);
		if (ret_size > sizes.size)
			sizes.size = ret_size;
		files = files->next;
	}
	return (sizes);
}

static inline void		longlist_uid_gid(t_file *file)
{
	struct passwd		*pw;
	struct group		*gr;
	char				*buf;

	pw = getpwuid(file->st_uid);
	gr = getgrgid(file->st_gid);
	if (!(buf = (char *)malloc(sizeof(char)
			* (ft_strlen(pw->pw_name) + ft_strlen(gr->gr_name)) + 6)))
		return ;
	*buf = ' ';
	ft_strcpy(buf + 1, pw->pw_name);
	ft_strcat(buf, "  ");
	ft_strcat(buf, gr->gr_name);
	ft_strcat(buf, "  ");
	ft_putstr(buf);
	free(buf);
}

static inline void		print_longlist(t_file *file, t_sizes *spaces)
{
	char				buf_mode[13];
	char				buf_time[23];

	longlist_modes(file, buf_mode);
	ft_putstr(buf_mode);
	ft_putnbr_ralign(file->st_nlink, spaces->nlink);
	longlist_uid_gid(file);
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
	if (g_options.multi_files)
	{
		ft_putstr(dir_name);
		ft_putstr(":\n");
	}
	if (g_options.format == long_listing)
	{
		sizes = get_sizes(tmp);
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
