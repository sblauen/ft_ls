/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 14:52:11 by sblauens          #+#    #+#             */
/*   Updated: 2018/07/14 01:23:13 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS

#include "libft.h"
#include "options.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>

extern t_options		g_options;

typedef struct			s_timespec
{
	time_t				tv_sec;
	long				tv_nsec;
}						t_timespec;

typedef struct			s_file
{
	t_timespec			mtime;
	off_t				size;
	char				filename[256];
	char				parentname[256];
	char				pathname[260];
	mode_t				st_mode;
}						t_file;

void					list_content(char *dir_name);
int						get_dir_content(char *dir_name, DIR *dir_stream,
											t_list **dir_files);
void					print_dir(char *dir_name, t_list *dir_files);
void					del_file_node(void *content, size_t size);
void					check_options(int ac, char **av, int *n);
void					check_files(char **av);
int						cmp_files(void *f1, void *f2);
void					error_put(char *filename);
#endif
