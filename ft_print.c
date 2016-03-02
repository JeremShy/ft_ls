/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 14:39:55 by jcamhi            #+#    #+#             */
/*   Updated: 2016/03/02 15:03:08 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static int	find_total(t_file *list)
{
	int	total;

	total = 0;
	while (list != NULL)
	{
		total += list->blocks; 
		list = list->next;
	}
	return (total);
}

static void	ft_print_with_l(t_file *list, int print_total)
{
	t_max	max;

	max = find_max(list);
	if (print_total)
		ft_printf("total %d\n", find_total(list));
	while(list != NULL)
	{
		ft_printf("%*s ", max.rights, list->rights);
		ft_printf("%*d ", max.nlinks + 1, list->nlinks);
		ft_printf("%*s ", (max.owner_name + 1) * -1, list->owner_name);
		ft_printf("%*s ", (max.group_name + 1) * -1, list->group_name);
		if (list->rights[0] == 'c' || list->rights[0] == 'b')
		{
			ft_printf("%*d, ", max.major, list->major);
			ft_printf("%*d ", max.minor, list->minor);
		}
		else
			ft_printf("%*d ", max.nbytes + 1, list->nbytes);
		ft_printf("%s %s %s:%s ", list->mounth, list->day_nbr,
				list->hour, list->min);
		ft_printf("%s", list->name);
		if (list->path_to_lnk)
			ft_printf(" -> %s", list->path_to_lnk);
		ft_printf("\n");
		list = list->next;
	}
}


static void	ft_print_normal(t_file *list)
{
	while (list)
	{
		ft_printf("%s\n", list->name);
		list = list->next;
	}
}

void		ft_print(t_file *list, t_opt options, int print_total)
{
	if (options.l)
		ft_print_with_l(list, print_total);
	else
		ft_print_normal(list);
}
