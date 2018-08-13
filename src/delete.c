/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 15:34:42 by sblauens          #+#    #+#             */
/*   Updated: 2018/08/13 01:52:45 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void					del_file_node(void *content, size_t size)
{
	t_file				*file;

	(void)size;
	file = (t_file *)content;
	ft_memdel((void **)&(file->pathname));
	ft_memdel((void **)&(file->filename));
	if (g_options.format == long_listing)
	{
		ft_memdel((void **)&(file->pw_name));
		ft_memdel((void **)&(file->gr_name));
	}
	ft_memdel(&content);
}

void					del_args_node(void *content, size_t size)
{
	t_file				*file;

	(void)size;
	file = (t_file *)content;
	ft_memdel((void **)&(file->pathname));
	ft_memdel((void **)&(file->pw_name));
	ft_memdel((void **)&(file->gr_name));
	ft_memdel(&content);
}

void					del_nodes(void *content, size_t size)
{
	(void)size;
	ft_memdel(&content);
}
