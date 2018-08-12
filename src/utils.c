/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 16:00:56 by sblauens          #+#    #+#             */
/*   Updated: 2018/08/12 15:31:52 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t					nbr_align(char *buf, int n, size_t sp)
{
	register size_t		len;
	register int		k;

	k = 10;
	buf[sp] = 0;
	len = sp;
	if (!n)
		buf[--sp] = '0';
	else
	{
		while (n)
		{
			buf[--sp] = n % 10 + '0';
			n /= 10;
		}
	}
	while (sp > 0)
		buf[--sp] = ' ';
	return (len);
}

/*
**  Make a new node containing the data of 'file_st' and add it to
**  the list pointed to by '*content'.
*/

void					add_new_node(t_list **content, t_file *file_st)
{
	t_list				*node;

	if (!(node = ft_lstnew(file_st, sizeof(*file_st))))
		return ;
	if (!*content)
		*content = node;
	else
		ft_lstadd_bck(content, node);
}
