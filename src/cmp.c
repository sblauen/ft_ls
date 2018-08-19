/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 13:53:52 by sblauens          #+#    #+#             */
/*   Updated: 2018/08/17 22:04:30 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline int		cmp_files_time(t_timespec *t1, t_timespec *t2)
{
	int					time_cmp;

	time_cmp = (int)(t2->tv_sec - t1->tv_sec);
	if (!time_cmp)
		time_cmp = (int)(t2->tv_nsec - t1->tv_nsec);
	return (time_cmp);
}

static inline int		cmp_files_size(off_t *t1, off_t *t2)
{
	int					size_cmp;

	size_cmp = (int)(*t2 - *t1);
	return (size_cmp);
}

int						cmp_files(void *f1, void *f2)
{
	int					cmp;

	cmp = 0;
	if (g_options.reverse)
		ft_swapptr(&f1, &f2);
	if (g_options.sort == by_time)
		cmp = cmp_files_time(&((t_file *)f1)->time, &((t_file *)f2)->time);
	if (g_options.sort == by_size)
		cmp = cmp_files_size(&((t_file *)f1)->st_size, &((t_file *)f2)->st_size);
	if (!cmp)
		cmp = ft_strcmp(((t_file *)f1)->filename, ((t_file *)f2)->filename);
	return (cmp);
}

int						cmp_args(void *s1, void *s2)
{
	return (ft_strcmp((const char *)s1, (const char *)s2));
}
