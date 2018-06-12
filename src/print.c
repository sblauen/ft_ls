/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:58:21 by sblauens          #+#    #+#             */
/*   Updated: 2018/06/12 02:17:03 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern t_options	g_options;

void				print_dir(t_list *dir_files)
{
	t_list		*tmp;

	tmp = dir_files;
	if (g_options.multi_files)
	{
		ft_putstr(((t_file *)(tmp->content))->parentname);
		ft_putstr(":\n");
	}
	while (tmp)
	{
		ft_putendl(((t_file *)(tmp->content))->filename);
		tmp = tmp->next;
	}
}
