/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 16:51:34 by sblauens          #+#    #+#             */
/*   Updated: 2018/07/13 02:01:00 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline void				iter_file_args(t_list *file_args)
{
	t_list			*tmp;

	tmp = file_args;
	while (tmp)
	{
		if (!S_ISDIR(((t_file *)(tmp->content))->st_mode))
			ft_putendl(((t_file *)(tmp->content))->filename);
		tmp = tmp->next;
	}
	tmp = file_args;
	while (tmp)
	{
		if (S_ISDIR(((t_file *)(tmp->content))->st_mode))
		{
			ft_putstr("\n");
			list_dir_content(((t_file *)(tmp->content))->filename);
		}
		tmp = tmp->next;
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
		if (stat(*av, &statbuf))
			error_put(*av);
		else
		{
			ft_strcpy(arg.filename, *av);
			arg.mtime.tv_sec = statbuf.st_mtim.tv_sec;
			arg.mtime.tv_nsec = statbuf.st_mtim.tv_nsec;
			arg.st_mode = statbuf.st_mode;
			if (!(node = ft_lstnew(&arg, sizeof(arg))))
				return (NULL);
			if (!file_args)
				file_args = node;
			else
				ft_lstadd_bck(&file_args, node);
		}
		++av;
	}
	return (file_args);
}

void							check_files(char **av)
{
	t_list		*args;

	args = NULL;
	if (*av)
	{
		args = parse_file_args(av);
		if (args)
		{
			ft_lstsort_merge(&args, &cmp_files);
			iter_file_args(args);
			ft_lstdel(&args, &del_file_node);
		}
	}
	else
		list_dir_content(".");
}
