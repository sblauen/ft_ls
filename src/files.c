/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 16:51:34 by sblauens          #+#    #+#             */
/*   Updated: 2018/06/12 17:02:01 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline void				iter_file_args(t_list *file_args)
{
	while (file_args)
	{
		list_dir_content((char *)file_args->content);
		file_args = file_args->next;
		if (file_args)
			ft_putstr("\n");
	}
}

static inline t_list			*parse_file_args(char **av)
{
	size_t			arg_len;
	t_list			*file_args;
	t_list			*node;

	file_args = NULL;
	while (*av)
	{
		node = NULL;
		arg_len = ft_strlen(*av);
		if (!(node = ft_lstnew(*av, arg_len)))
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
		ft_lstsort_merge(&files, &cmp_dirname);
		iter_file_args(files);
		ft_lstdel(&files, &del_file_node);
	}
	else
		list_dir_content(".");
}
