/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:58:21 by sblauens          #+#    #+#             */
/*   Updated: 2018/08/11 20:09:59 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline void		print_longlist(t_list *files)
{
	char				*buf;
	char				tot[18];
	t_list				*tmp;
	t_sizes				sizes;

	tmp = files;
	if (tmp)
	{
		longlist_sizes(tmp, &sizes);
		ft_strcpy(tot, "total ");
		nbr_align(tot + 6, sizes.blocks ,ft_nbrdgts(sizes.blocks));
		ft_putendl(tot);
	}
	if (!(buf = ft_strnew(sizes.len)))
		return ;
	while (tmp)
	{
		longlist_buf(((t_file *)(tmp->content)), &sizes, buf);
		ft_putendl(buf);
		tmp = tmp->next;
	}
	ft_memdel((void **)&buf);
}

void					print_dir(t_list *dir_files)
{
	t_list				*tmp;

	tmp = dir_files;
	if (g_options.format == long_listing)
	{
		print_longlist(dir_files);
	}
	else
		while (tmp)
		{
			ft_putendl(((t_file *)(tmp->content))->filename);
			tmp = tmp->next;
		}
}
