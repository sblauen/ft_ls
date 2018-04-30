/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 15:09:13 by sblauens          #+#    #+#             */
/*   Updated: 2018/05/01 01:13:20 by sblauens         ###   ########.fr       */
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
	t_list				*subdir_files;
	struct stat			statbuf;

	while (dir_files)
	{
		subdir_files = NULL;
		if (ft_strcmp(((t_file *)(dir_files->content))->filename, ".")
				&& ft_strcmp(((t_file *)(dir_files->content))->filename, ".."))
		{
			if (stat(((t_file *)(dir_files->content))->pathname, &statbuf))
				error_exit();
			if (S_ISDIR(statbuf.st_mode))
				list_dir_content(((t_file *)(dir_files->content))->pathname,
						&subdir_files, options);
		}
		((t_file *)(dir_files->content))->subfiles = subdir_files;
		dir_files = dir_files->next;
	}
}

int					list_dir_content(char *dir_name, t_list **dir_files,
										const t_options *options)
{
	DIR					*dir_stream;

	errno = 0;
	if (!(dir_stream = opendir(dir_name)))
		error_exit();
	get_dir_content(dir_name,dir_stream, dir_files, options);
	print_dir_content(*dir_files);
	if (options->recursive)
		recursive_list(*dir_files, options);
	if (closedir(dir_stream) == -1)
		error_exit();
	return (0);
}
