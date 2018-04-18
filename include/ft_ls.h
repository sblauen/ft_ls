/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 14:52:11 by sblauens          #+#    #+#             */
/*   Updated: 2018/04/18 17:17:12 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS

#include "libft.h"
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>

typedef struct			s_dir
{
	off_t				size;
	char				name[256];
	struct timespec		*date;
}						t_dir;

int						read_dir(char *dir_name, t_list **dir_files);
#endif
