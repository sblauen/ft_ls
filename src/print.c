/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:58:21 by sblauens          #+#    #+#             */
/*   Updated: 2018/07/29 19:42:42 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>
#include "ft_ls.h"

static inline size_t	get_spaces(t_list *files)
{
	size_t				spaces_nlink;
	size_t				ret_nlink;

	spaces_nlink = 0;
	while (files)
	{
		ret_nlink = ft_nbrpwr(((t_file *)(files->content))->st_nlink);
		if (ret_nlink > spaces_nlink)
			spaces_nlink = ret_nlink;
		files = files->next;
	}
	return (spaces_nlink);
}

static inline void		longlist_link_uid_gid(t_file *file, size_t spaces_nlink)
{
	struct passwd		*pw;
	struct group		*gr;
	char				*buf;

	pw = getpwuid(file->st_uid);
	gr = getgrgid(file->st_gid);
	ft_putnbr_ralign(file->st_nlink, spaces_nlink);
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

static inline void		print_longlist(t_file *file, size_t spaces_nlink)
{
	char				buf[13];

	longlist_modes(file, buf);
	buf[10] = ' ';
	buf[11] = ' ';
	buf[12] = 0;
	ft_putstr(buf);
	longlist_link_uid_gid(file, spaces_nlink);
}

void					print_dir(char *dir_name, t_list *dir_files)
{
	t_list				*tmp;
	size_t				spaces_nlink;

	tmp = dir_files;
	if (g_options.multi_files)
	{
		ft_putstr(dir_name);
		ft_putstr(":\n");
	}
	spaces_nlink = get_spaces(tmp);
	while (tmp)
	{
		if (g_options.format == long_listing)
			print_longlist(((t_file *)(tmp->content)), spaces_nlink);
		ft_putendl(((t_file *)(tmp->content))->filename);
		tmp = tmp->next;
	}
}
