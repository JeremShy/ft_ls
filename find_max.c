/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_max.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 15:53:29 by jcamhi            #+#    #+#             */
/*   Updated: 2016/01/22 15:54:14 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static int		len(int nbr)
{
	char    *str;
	int     ret;

	str = ft_itoa_base_ll((long long)nbr, 10);
	ret = ft_strlen(str);
	free(str);
	return (ret);
}

static t_max	init_max(void)
{
	t_max max;

	max.name = 0;
	max.fileno = 0;
	max.rights = 0;
	max.nlinks = 0;
	max.owner_name = 0;
	max.group_name = 0;
	max.nbytes = 0;
	return (max);
}

static void		do_compare(int *n1, int n2)
{
	if (*n1 < n2)
		*n1 = n2;
}

static void		comp_max(t_file list, t_max *max)
{
	do_compare(&(max->name), list.name_len);
	do_compare(&(max->fileno), len(list.fileno));
	do_compare(&(max->rights), ft_strlen(list.rights));
	do_compare(&(max->nlinks), len(list.nlinks));
	do_compare(&(max->owner_name), ft_strlen(list.owner_name));
	do_compare(&(max->group_name), ft_strlen(list.group_name));
	do_compare(&(max->nbytes), len(list.nbytes));
}

t_max			find_max(t_file *list)
{
	t_max max;

	max = init_max();
	while (list != NULL)
	{
		comp_max(*list, &max);
		list = list->next;
	}
	return (max);
}
