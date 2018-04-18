/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 15:09:13 by sblauens          #+#    #+#             */
/*   Updated: 2018/04/18 17:19:17 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				error_exit(void)
{
	perror("ft_ls: ");
	exit(EXIT_FAILURE);

}

int					read_dir(char *dir_name, t_list **dir_files)
{
	t_dir				dir_info;
	t_list				*node;
	DIR					*dir_stream;
	struct dirent		*dir_ent;

	errno = 0;
	dir_stream = opendir(dir_name);
	if (!dir_stream)
		error_exit();
	while ((dir_ent = readdir(dir_stream)))
	{
		ft_strcpy(dir_info.name, dir_ent->d_name);
		if (!(node = ft_lstnew(&dir_info, sizeof(dir_info))))
			return (-1);
		if (!*dir_files)
			*dir_files = node;
		else
			ft_lstadd_bck(dir_files, node);
	}
	if (closedir(dir_stream) == -1)
		error_exit();
	return (0);
}
