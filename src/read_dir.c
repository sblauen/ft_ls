/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 15:09:13 by sblauens          #+#    #+#             */
/*   Updated: 2018/04/13 09:11:25 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list				*read_dir(char *dir_name)
{
	t_dir				dir_info;
	t_list				*dir_lst;
	t_list				*node;
	DIR					*dir_stream;
	struct dirent		*dir_ent;

	errno = 0;
	dir_lst = NULL;
	dir_stream = opendir(dir_name);
	if (!dir_stream)
	{
		perror("ft_ls: ");
		exit(EXIT_FAILURE);
	}
	while ((dir_ent = readdir(dir_stream)))
	{
		ft_strcpy(dir_info.name, dir_ent->d_name);
		if (!(node = ft_lstnew(&dir_info, sizeof(dir_info))))
			return (NULL);
		if (!dir_lst)
			dir_lst = node;
		else
			ft_lstadd_bck(&dir_lst, node);
	}
	if (closedir(dir_stream) == -1)
	{
		perror("ft_ls: ");
		exit(EXIT_FAILURE);
	}
	return (dir_lst);
}
