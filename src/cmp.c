/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 13:53:52 by sblauens          #+#    #+#             */
/*   Updated: 2018/06/13 03:22:30 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

extern t_options				g_options;

int								cmp_filename(void *f1, void *f2)
{
	if (g_options.reverse)
		return (ft_strcmp(((t_file *)f2)->filename, ((t_file *)f1)->filename));
	else
		return (ft_strcmp(((t_file *)f1)->filename, ((t_file *)f2)->filename));
}

int								cmp_dirname(void *d1, void *d2)
{
	if (g_options.reverse)
		return (ft_strcmp((char *)d2, (char *)d1));
	else
		return (ft_strcmp((char *)d1, (char *)d2));
}
