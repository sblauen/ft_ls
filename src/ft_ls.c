/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 11:59:22 by sblauens          #+#    #+#             */
/*   Updated: 2018/08/18 23:10:14 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int						main(int ac, char **av)
{
	int					n;
	int					ret;
	t_file				dot;

	n = 1;
	ret = 0;
	errno = 0;
	check_options(ac, av, &n);
	if (*(av + n))
		ret = check_files(av + n);
	else
	{
		dot.pathname = ft_strdup(".");
		dot.filename = dot.pathname;
		ret = list_content(&dot);
		free(dot.pathname);
	}
	return (ret);
}
