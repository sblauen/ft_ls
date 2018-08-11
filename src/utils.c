/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 16:00:56 by sblauens          #+#    #+#             */
/*   Updated: 2018/08/11 16:01:31 by sblauens         ###   ########.fr       */
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
