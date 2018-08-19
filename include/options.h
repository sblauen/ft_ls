/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 20:12:45 by sblauens          #+#    #+#             */
/*   Updated: 2018/08/13 23:59:59 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONS_H
# define OPTIONS_H

typedef enum			e_dotfiles_options
{
	none,
	almost_all,
	all
}						t_dotfiles_options;

typedef enum			e_format_options
{
	column,
	long_listing,
	one_per_line
}						t_format_options;

typedef enum			e_sort_options
{
	unsorted,
	name,
	by_time
}						t_sort_options;

typedef enum			e_time_options
{
	modif_time,
	change_time,
	access_time
}						t_time_options;

typedef struct			s_options
{
	unsigned int		multi_files;
	t_dotfiles_options	dotfiles;
	t_format_options	format;
	unsigned int		recursive;
	unsigned int		reverse;
	t_sort_options		sort;
	t_time_options		time;
}						t_options;
#endif
