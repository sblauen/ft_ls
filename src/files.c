/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 16:51:34 by sblauens          #+#    #+#             */
/*   Updated: 2018/08/13 01:15:58 by sblauens         ###   ########.fr       */
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
			ft_putendl(((t_file *)(tmp->content))->pathname);
		tmp = tmp->next;
	}
	tmp = file_args;
	while (tmp)
	{
		if (S_ISDIR(((t_file *)(tmp->content))->st_mode))
			list_content(((t_file *)(tmp->content)));
		tmp = tmp->next;
	}
}

static inline int				get_stat(char *path, struct stat *sb)
{
	if (g_options.format == long_listing)
	{
		if (lstat(path, sb))
			return (-1);
	}
	else
	{
		if (stat(path, sb))
			return (-1);
	}
	return (0);
}

static inline t_list			*parse_file_args(char **av)
{
	t_list			*file_args;
	t_file			arg;
	struct stat		statbuf;

	file_args = NULL;
	while (*av)
	{
		arg.pathname = *av;
		if (get_stat(arg.pathname, &statbuf))
			error_put(&arg);
		else
		{
			arg.pathname = ft_strdup(*av);
			arg.filename = arg.pathname;
			arg.mtime.tv_sec = statbuf.st_mtim.tv_sec;
			arg.mtime.tv_nsec = statbuf.st_mtim.tv_nsec;
			arg.st_mode = statbuf.st_mode;
			arg.pw_name = NULL;
			arg.gr_name = NULL;
			add_new_node(&file_args, &arg);
		}
		++av;
	}
	return (file_args);
}

void							check_files(char **av)
{
	t_list		*args;
	t_file		dot;

	args = NULL;
	if (*av)
	{
		args = parse_file_args(av);
		if (args)
		{
			ft_lstsort_merge(&args, &cmp_files);
			iter_file_args(args);
			ft_lstdel(&args, &del_args_node);
		}
	}
	else
	{
		dot.pathname = ft_strdup(".");
		dot.filename = dot.pathname;
		list_content(&dot);
		free(dot.pathname);
	}
}
