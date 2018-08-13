/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 16:51:34 by sblauens          #+#    #+#             */
/*   Updated: 2018/08/13 02:47:36 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline void		print_files(t_list *files)
{
	char				*buf;
	t_sizes				sizes;

	buf = NULL;
	if (g_options.format == long_listing)
	{
		longlist_sizes(files, &sizes);
		if (!(buf = ft_strnew(sizes.len)))
			return ;
		while (files)
		{
			longlist_buf(((t_file *)(files->content)), &sizes, buf);
			ft_putendl(buf);
			files = files->next;
		}
		ft_memdel((void **)&buf);
	}
	while (files)
	{
		ft_putendl(((t_file *)(files->content))->pathname);
		files = files->next;
	}
}

static inline void		iter_file_args(t_list *file_args)
{
	t_list				*tmp;
	t_list				*files;

	tmp = file_args;
	files = NULL;
	while (tmp)
	{
		if (!S_ISDIR(((t_file *)(tmp->content))->st_mode))
			add_new_node(&files, (t_file *)(tmp->content));
		tmp = tmp->next;
	}
	if (files)
	{
		print_files(files);
		if (ft_lstsize(file_args) > ft_lstsize(files))
			ft_putchar('\n');
		ft_lstdel(&files, &del_nodes);
	}
	tmp = file_args;
	while (tmp)
	{
		if (S_ISDIR(((t_file *)(tmp->content))->st_mode))
			list_content(((t_file *)(tmp->content)));
		tmp = tmp->next;
	}
}

static inline int		get_stat(char *path, t_file *arg)
{
	struct stat			statbuf;
	struct passwd		*pw;
	struct group		*gr;

	if ((g_options.format == long_listing) && lstat(path, &statbuf))
		return (-1);
	else if ((g_options.format != long_listing) && stat(path, &statbuf))
		return (-1);
	arg->st_mode = statbuf.st_mode;
	arg->mtime.tv_sec = statbuf.st_mtim.tv_sec;
	arg->mtime.tv_nsec = statbuf.st_mtim.tv_nsec;
	arg->st_nlink = statbuf.st_nlink;
	arg->st_size = statbuf.st_size;
	arg->st_rdev = statbuf.st_rdev;
	if ((pw = getpwuid(statbuf.st_uid)))
		arg->pw_name = ft_strdup(pw->pw_name);
	else
		arg->pw_name = ft_itoa(statbuf.st_uid);
	if ((gr = getgrgid(statbuf.st_gid)))
		arg->gr_name = ft_strdup(gr->gr_name);
	else
		arg->gr_name = ft_itoa(statbuf.st_gid);
	return (0);
}

static inline t_list	*parse_file_args(char **av)
{
	t_list				*file_args;
	t_file				arg;

	file_args = NULL;
	arg.filename = NULL;
	while (*av)
	{
		arg.pathname = *av;
		arg.st_blocks = 0;
		if (get_stat(arg.pathname, &arg))
			error_put(&arg);
		else
		{
			arg.pathname = ft_strdup(*av);
			arg.filename = arg.pathname;
			add_new_node(&file_args, &arg);
		}
		++av;
	}
	return (file_args);
}

void					check_files(char **av)
{
	t_list				*args;
	t_file				dot;

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
