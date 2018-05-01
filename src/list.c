/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 15:09:13 by sblauens          #+#    #+#             */
/*   Updated: 2018/05/01 03:28:53 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				error_exit(void)
{
	perror("ft_ls: ");
	exit(EXIT_FAILURE);

}

void				recursive_list(t_list *dir_files, const t_options *options)
{
	struct stat			statbuf;

	while (dir_files)
	{
		if (ft_strcmp(((t_file *)(dir_files->content))->filename, ".")
				&& ft_strcmp(((t_file *)(dir_files->content))->filename, ".."))
		{
			if (stat(((t_file *)(dir_files->content))->pathname, &statbuf))
				error_exit();
			if (S_ISDIR(statbuf.st_mode))
				list_dir_content(((t_file *)(dir_files->content))->pathname,
										options);
		}
		dir_files = dir_files->next;
	}
}

int					list_dir_content(char *dir_name, const t_options *options)
{
	DIR					*dir_stream;
	t_list				*dir_files;

	errno = 0;
	dir_files = NULL;
	if (!(dir_stream = opendir(dir_name)))
		error_exit();
	get_dir_content(dir_name, dir_stream, &dir_files, options);
	if (closedir(dir_stream) == -1)
		error_exit();
	print_dir_content(dir_files);
	if (options->recursive)
		recursive_list(dir_files, options);
	ft_lstdel(&dir_files, &del_file_node);
	return (0);
}
