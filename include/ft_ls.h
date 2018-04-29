/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 14:52:11 by sblauens          #+#    #+#             */
/*   Updated: 2018/04/29 22:18:18 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS

#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include "options.h"

typedef struct			s_file
{
	off_t				size;
	char				filename[256];
	char				pathname[256];
	struct timespec		*date;
	t_list				*subfiles;
}						t_file;

int						get_dir_content(char *dir_name, t_list **dir_files);
void					print_dir_content(t_list *dir_files);
void					del_recursive_list(t_list **dir_files);
void					default_options(t_options *options);
void					parse_option_args(char *arguments, t_options *options);
#endif
