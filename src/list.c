/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 15:09:13 by sblauens          #+#    #+#             */
/*   Updated: 2018/08/18 23:20:02 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**  List recursively a directory's 'content' if specified as option.
*/

static inline int		recursive_list(t_list *content)
{
	int					ret;
	t_file				*file;

	ret = 0;
	while (content)
	{
		file = (t_file *)(content->content);
		if (ft_strcmp(file->filename, ".") && ft_strcmp(file->filename, ".."))
			if (S_ISDIR(file->st_mode))
				ret = list_content(file);
		content = content->next;
	}
	return (ret);
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

int						list_content(t_file *dir)
{
	int					ret;
	t_list				*content;
	static int			n = -1;

	ret = 0;
	if (!n)
		ft_putchar('\n');
	if  (g_options.multi_files || (g_options.recursive && !n))
		list_dirname(dir->pathname);
	if (!(ret = get_content(dir, &content)) && content)
	{
		ft_lstsort_merge(&content, &cmp_files);
		print_dir(content);
	}
	n = 0;
	if (g_options.recursive)
		if (recursive_list(content))
			ret = 1;
	if (content)
		ft_lstdel(&content, &del_file_node);
	return (ret);
}
