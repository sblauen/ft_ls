/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 22:23:14 by sblauens          #+#    #+#             */
/*   Updated: 2018/08/07 00:45:43 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				error_put(t_file *file)
{
	ft_putstr_fd("ft_ls: ", 2);
	if (*(file->filename))
		perror(file->filename);
	else
		perror(file->pathname);
}
