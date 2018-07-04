/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 16:51:34 by sblauens          #+#    #+#             */
/*   Updated: 2018/07/04 03:39:31 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline void				iter_file_args(t_list *file_args)
{
	while (file_args)
	{
		list_dir_content(((t_file *)(file_args->content))->filename);
		file_args = file_args->next;
		if (file_args)
			ft_putstr("\n");
	}
}

static inline t_list			*parse_file_args(char **av)
{
	t_list			*file_args;
	t_list			*node;
	t_file			arg;
	struct stat		statbuf;

	file_args = NULL;
	while (*av)
	{
		ft_strcpy(arg.filename, *av);
		if (stat(arg.filename, &statbuf))
			error_exit();
		arg.mtime.tv_sec = statbuf.st_mtim.tv_sec;
		arg.mtime.tv_nsec = statbuf.st_mtim.tv_nsec;
		if (!(node = ft_lstnew(&arg, sizeof(arg))))
			return (NULL);
		if (!file_args)
			file_args = node;
		else
			ft_lstadd_bck(&file_args, node);
		++av;
	}
	return (file_args);
}

void							check_files(char **av)
{
	t_list		*files;

	files = NULL;
	if (*av)
	{
		files = parse_file_args(av);
		ft_lstsort_merge(&files, &cmp_files);
		iter_file_args(files);
		ft_lstdel(&files, &del_file_node);
	}
	else
		list_dir_content(".");
}
