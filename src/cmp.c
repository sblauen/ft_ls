/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 13:53:52 by sblauens          #+#    #+#             */
/*   Updated: 2018/05/31 23:21:35 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			cmp_filename(void *f1, void *f2)
{
	return (ft_strcmp(((t_file *)f1)->filename, ((t_file *)f2)->filename));
}

int			cmp_dirname(void *d1, void *d2)
{
	return (ft_strcmp((char *)d1, (char *)d2));
}
