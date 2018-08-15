/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 22:23:14 by sblauens          #+#    #+#             */
/*   Updated: 2018/08/15 15:59:39 by sblauens         ###   ########.fr       */
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
