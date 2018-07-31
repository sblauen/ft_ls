/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:58:21 by sblauens          #+#    #+#             */
/*   Updated: 2018/07/31 03:37:54 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline t_sizes	get_sizes(t_list *files)
{
	size_t				ret_nlink;
	size_t				ret_size;
	size_t				ret_uid;
	t_sizes				sizes;

	sizes.nlink = 0;
	sizes.size = 0;
	sizes.blocks = 0;
	sizes.uid = 0;
	while (files)
	{
		sizes.blocks += ((t_file *)(files->content))->st_blocks;
		ret_nlink = ft_nbrpwr(((t_file *)(files->content))->st_nlink);
		if (ret_nlink > sizes.nlink)
			sizes.nlink = ret_nlink;
		ret_size = ft_nbrpwr(((t_file *)(files->content))->st_size);
		if (ret_size > sizes.size)
			sizes.size = ret_size;
		ret_uid = ft_strlen(((t_file *)(files->content))->pw_name);
		if (ret_uid > sizes.uid)
			sizes.uid = ret_uid;
		files = files->next;
	}
	return (sizes);
}

static inline void		longlist_uid_gid(t_file *file, t_sizes *spaces)
{
	char				*buf;
	size_t				pw_len;

	pw_len = ft_strlen(file->pw_name);
	if (!(buf = (char *)malloc(sizeof(char)
			* (spaces->uid + ft_strlen(file->gr_name)) + 6)))
		return ;
	*buf = ' ';
	ft_strcpy(buf + 1, file->pw_name);
	free(file->pw_name);
	ft_strncat_chr(buf + pw_len + 1, ' ', spaces->uid - pw_len + 2);
	ft_strcat(buf, file->gr_name);
	free(file->gr_name);
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
	longlist_uid_gid(file, spaces);
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
