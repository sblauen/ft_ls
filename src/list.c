/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 15:09:13 by sblauens          #+#    #+#             */
/*   Updated: 2018/07/31 18:39:32 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**  List recursively a directory's 'content' if specified as option.
*/

static inline void		recursive_list(t_list *content)
{
	t_file				*file;

	while (content)
	{
		file = (t_file *)(content->content);
		if (ft_strcmp(file->filename, ".") && ft_strcmp(file->filename, ".."))
			if (S_ISDIR(file->st_mode))
				list_content(file->pathname);
		content = content->next;
	}
}

static inline void		list_dirname(char *dir_name)
{
	ft_putstr(dir_name);
	ft_putstr(":\n");
}

/*
**  list the content of the directory 'dir_name'.
**
**  if an error occurs, a message using errno is written to standard error.
*/

void					list_content(char *dir_name)
{
	t_list				*dir_content;
	static int			n = -1;

	if (g_options.multi_files)
	{
		if (!n)
			ft_putchar('\n');
		list_dirname(dir_name);
	}
	if (!(get_content(dir_name, &dir_content)))
	{
		ft_lstsort_merge(&dir_content, &cmp_files);
		print_dir(dir_name, dir_content);
	}
	n = 0;
	if (g_options.recursive)
		recursive_list(dir_content);
	if (dir_content)
		ft_lstdel(&dir_content, &del_file_node);
}
