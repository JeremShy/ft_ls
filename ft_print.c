/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 14:39:55 by jcamhi            #+#    #+#             */
/*   Updated: 2016/01/22 17:36:42 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void		print_sp(int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		ft_putchar(' ');
		i++;
	}
}

void			ft_print_with_l(t_file *list)
{
	t_max	max;

	max = find_max(list);
	while(list != NULL)
	{
		ft_printf("%s ", list->rights);
		print_sp(max.nlinks - len(list->nlinks) + max.rights - ft_strlen(list->rights));
		ft_printf("%d ", list->nlinks);
		print_sp(max.owner_name - ft_strlen(list->owner_name) + max.owner_name - ft_strlen(list->owner_name));
		ft_printf("%s ", list->owner_name);
		print_sp(1 + max.group_name - ft_strlen(list->group_name) + max.group_name - ft_strlen(list->group_name));
		ft_printf("%s\n", list->group_name);
		list = list->next;
	}
}
