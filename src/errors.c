/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 22:23:14 by sblauens          #+#    #+#             */
/*   Updated: 2018/08/17 23:12:59 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void					error_put(t_file *file)
{
	ft_putstr_fd("ft_ls: ", 2);
	if (file->filename)
		perror(file->filename);
	else
		perror(file->pathname);
}

void					error_options(char argument)
{
	ft_putstr_fd("ft_ls: invalid option -- ", 2);
	ft_putchar_fd(argument, 2);
	ft_putstr_fd("\nUsage: ./ft_ls [-", 2);
	ft_putstr_fd(OPTIONS, 2);
	ft_putendl_fd("] [file ...]", 2);
	exit(EXIT_FAILURE);
}

int						error_args(char *argument)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(argument, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (1);
}
