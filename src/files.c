/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 16:51:34 by sblauens          #+#    #+#             */
/*   Updated: 2018/08/18 20:20:36 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline void		iter_files(t_list *args)
{
	t_list				*tmp;
	t_list				*files;

	tmp = args;
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
		if (ft_lstsize(args) > ft_lstsize(files))
			ft_putchar('\n');
		ft_lstdel(&files, &del_nodes);
	}
	tmp = args;
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
		return (1);
	else if ((g_options.format != long_listing) && stat(path, &statbuf))
		if (lstat(path, &statbuf))
			return (1);
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

static inline t_list	*get_filenames(char **av)
{
	t_list				*filenames;
	t_list				*node;

	filenames = NULL;
	while (*av)
	{
		node = ft_lstnew(NULL, 0);
		node->content = *av;
		if (!filenames)
			filenames = node;
		else
			ft_lstadd_bck(&filenames, node);
		++av;
	}
	ft_lstsort_merge(&filenames, &cmp_args);
	return (filenames);
}

static inline int		parse_files(t_list **files, t_list *filenames)
{
	int					ret;
	t_file				file;

	ret = 0;
	while (filenames)
	{
		if (get_stat((char *)(filenames->content), &file))
		{
			ret = error_args((char *)(filenames->content));
		}
		else
		{
			file.pathname = ft_strdup((char *)(filenames->content));
			file.filename = file.pathname;
			file.st_blocks = 0;
			add_new_node(files, &file);
		}
		filenames = filenames->next;
	}
	ft_lstsort_merge(files, &cmp_files);
	return (ret);
}

int						check_files(char **av)
{
	int					ret;
	t_file				dot;
	t_list				*names;
	t_list				*files;

	ret = 0;
	names = NULL;
	files = NULL;
	if (*av && (names = get_filenames(av)))
	{
		ret = parse_files(&files, names);
		ft_lstdel(&names, &set_null);
		if (files)
		{
			iter_files(files);
			ft_lstdel(&files, &del_args_node);
		}
		return (ret);
	}
	dot.pathname = ft_strdup(".");
	dot.filename = dot.pathname;
	list_content(&dot);
	free(dot.pathname);
	return (ret);
}
