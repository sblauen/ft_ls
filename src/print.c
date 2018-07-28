/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:58:21 by sblauens          #+#    #+#             */
/*   Updated: 2018/07/28 20:22:00 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline void	print_longlist(t_file *file)
{
	char			buf[12];

	longlist_modes(file, buf);
	buf[10] = ' ';
	buf[11] = 0;
	ft_putstr(buf);
}

void				print_dir(char *dir_name, t_list *dir_files)
{
	t_list		*tmp;

	tmp = dir_files;
	if (g_options.multi_files)
	{
		ft_putstr(dir_name);
		ft_putstr(":\n");
	}
	while (tmp)
	{
		if (g_options.format == long_listing)
			print_longlist(((t_file *)(tmp->content)));
		ft_putendl(((t_file *)(tmp->content))->filename);
		tmp = tmp->next;
	}
}
