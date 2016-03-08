/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 11:22:43 by jcamhi            #+#    #+#             */
/*   Updated: 2016/03/08 15:51:44 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

long long	ft_rights(t_file *elem1, t_file *elem2, t_opt opt)
{
	if (elem1->rights[0] == 'd' && elem2->rights[0] != 'd')
		return (1);
	else if (elem1->rights[0] != 'd' && elem2->rights[0] == 'd')
		return (-1);
	else
	{
		if (!opt.t && !opt.r)
			return (ft_lexic(elem1, elem2, opt));
		else if (opt.t && !opt.r)
			return (ft_mod(elem1, elem2, opt));
		else if (opt.t && opt.r)
			return (ft_mod_inv(elem1, elem2, opt));
		else if (!opt.t && opt.r)
			return (ft_lexic_inv(elem1, elem2, opt));
	}
	return (0);
}

static int	norme_sort(t_file **prev, t_file **debut, t_file **list)
{
	t_file *tmp;

	if (*prev)
		(*prev)->next = (*list)->next;
	if (*list == *debut)
		*debut = (*list)->next;
	tmp = ((*list)->next)->next;
	((*list)->next)->next = *list;
	(*list)->next = tmp;
	return (0);
}

t_file		*ft_sort(t_file *list, t_opt opt)
{
	long long	(*f)(t_file *, t_file *, t_opt);
	t_file		*debut;
	t_file		*prev;
	int			range;

	f = init_tab(opt);
	range = 0;
	debut = list;
	while (!range)
	{
		prev = NULL;
		range = 1;
		while (list && list->next)
		{
			if (f(list, list->next, opt) > 0)
				range = norme_sort(&prev, &debut, &list);
			prev = list;
			list = list->next;
		}
		list = debut;
	}
	return (debut);
}
