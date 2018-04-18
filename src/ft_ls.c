/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 11:59:22 by sblauens          #+#    #+#             */
/*   Updated: 2018/04/18 17:10:38 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			del_dir(void *content, size_t size)
{
	(void)size;
	ft_memdel(&content);
}

int				main(int ac, char **av)
{
	t_list		*a_lst;
	t_list		*tmp_lst;

	a_lst = NULL;
	if (ac > 1)
		read_dir(*(av + 1), &a_lst);
	else
		read_dir(".", &a_lst);
	while (a_lst)
	{
		printf("%s\n", ((t_dir *)(a_lst)->content)->name);
		tmp_lst = (a_lst)->next;
		/*ft_memdel(&(a_lst->content));*/
		/*ft_memdel((void **)&a_lst);*/
		ft_lstdelone(&a_lst,&del_dir);
		a_lst = tmp_lst;
	}
	return (0);
}
