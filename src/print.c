/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:58:21 by sblauens          #+#    #+#             */
/*   Updated: 2018/07/29 21:40:24 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
#include "ft_ls.h"

static inline t_spaces	get_spaces(t_list *files)
{
	size_t				ret_nlink;
	size_t				ret_size;
	t_spaces			spaces;

	spaces.nlink = 0;
	spaces.size = 0;
	while (files)
	{
		ret_nlink = ft_nbrpwr(((t_file *)(files->content))->st_nlink);
		if (ret_nlink > spaces.nlink)
			spaces.nlink = ret_nlink;
		ret_size = ft_nbrpwr(((t_file *)(files->content))->st_size);
		if (ret_size > spaces.size)
			spaces.size = ret_size;
		files = files->next;
	}
	return (spaces);
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

static inline void		print_longlist(t_file *file, t_spaces *spaces)
{
	char				buf[13];

	longlist_modes(file, buf);
	ft_putstr(buf);
	ft_putnbr_ralign(file->st_nlink, spaces->nlink);
	longlist_uid_gid(file);
	ft_putnbr_ralign(file->st_size, spaces->size);
	ft_putchar(' ');
}

void					print_dir(char *dir_name, t_list *dir_files)
{
	t_list				*tmp;
	t_spaces			spaces;

	tmp = dir_files;
	if (g_options.multi_files)
	{
		ft_putstr(dir_name);
		ft_putstr(":\n");
	}
	spaces = get_spaces(tmp);
	while (tmp)
	{
		if (g_options.format == long_listing)
			print_longlist(((t_file *)(tmp->content)), &spaces);
		ft_putendl(((t_file *)(tmp->content))->filename);
		tmp = tmp->next;
	}
}
