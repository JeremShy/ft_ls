/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 14:39:55 by jcamhi            #+#    #+#             */
/*   Updated: 2016/02/01 15:27:54 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static int	find_total(t_file *list, t_opt opt)
{
	int	total;

	total = 0;
	while (list != NULL)
	{
		if (list->name[0] != '.' || (list->name[0] == '.' && opt.a))
			total += list->blocks; 
		list = list->next;
	}
	return (total);
}

void		ft_print_with_l(t_file *list, t_opt opt)
{
	t_max	max;

	max = find_max(list);
	ft_printf("total %d\n", find_total(list, opt));
	while(list != NULL)
	{
		if (list->name[0] != '.' || (list->name[0] == '.' && opt.a))
		{
			ft_printf("%*s ", max.rights, list->rights);
			ft_printf("%*d", max.nlinks + 1, list->nlinks);
			ft_printf("%*s ", max.owner_name + 1, list->owner_name);
			ft_printf("%*s ", max.group_name + 1, list->group_name);
			ft_printf("%*d ", max.nbytes + 1, list->nbytes);
			ft_printf("%s %s %s:%s ", list->mounth, list->day_nbr,
					list->hour, list->min);
			ft_printf("%s\n", list->name);
		}
		list = list->next;
	}
}
