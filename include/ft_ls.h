/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 14:52:11 by sblauens          #+#    #+#             */
/*   Updated: 2018/08/11 16:25:02 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include "options.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <dirent.h>
# include <stdio.h>
# include <time.h>
# include <errno.h>

# ifdef __APPLE__
#  define MAJOR 24
# else
#  define MAJOR 8
# endif

extern t_options		g_options;

typedef struct			s_timespec
{
	time_t				tv_sec;
	long				tv_nsec;
}						t_timespec;

typedef struct			s_sizes
{
	quad_t				blocks;
	size_t				nlink;
	size_t				size;
	size_t				uid;
	size_t				gid;
	size_t				mjr;
	size_t				len;
}						t_sizes;

typedef struct			s_file
{
	t_timespec			mtime;
	char				filename[256];
	char				*pathname;
	char				*pw_name;
	char				*gr_name;
	off_t				st_size;
	quad_t				st_blocks;
	nlink_t				st_nlink;
	dev_t				st_rdev;
	mode_t				st_mode;
}						t_file;

void					list_content(t_file *dir);
int						get_content(t_file *dir, t_list **content);
void					print_dir(t_list *dir_files);
void					longlist_modes(t_file *file, char *buf);
void					longlist_sizes(t_list *files, t_sizes *sizes);
char					*longlist_buf(t_file *file, t_sizes *sp);
void					del_file_node(void *content, size_t size);
void					check_options(int ac, char **av, int *n);
void					check_files(char **av);
int						cmp_files(void *f1, void *f2);
void					error_put(t_file *file);
size_t					nbr_align(char *buf, int n, size_t sp);
#endif
