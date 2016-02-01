/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 15:31:11 by jcamhi            #+#    #+#             */
/*   Updated: 2016/02/01 19:07:59 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static int	ft_lexic(t_file *elem1, t_file *elem2)
{
	return (ft_strcmp(elem1->name, elem2->name));
}

t_file	*ft_sort(t_file *list, t_opt opt)
{
	static int	(*f)(t_file *, t_file *);
	t_file		*debut;
	t_file		*tmp;
	t_file		*prev;
	int			range;

	prev = NULL;
	if (!opt.t)
		f = ft_lexic;
	debut = list;
	range = 0;
	while (!range)
	{
		printf("on recommence\n");
		range = 1;
		while (list && list->next)
		{
			ft_printf("on compare %s et %s\n",list->name, list->next->name);
			if (f(list, list->next) > 0)
			{
				printf("on inverse %s et %s\n", list->name, list->next->name);
				ft_printf("avant: list %s, list->next %s\n", list->name, list->next->name);
				if (prev)
					prev->next = list->next;
//				if (list == debut)
//					debut = list->next;
				tmp = list->next;
				list->next = tmp->next;
				tmp->next = list;
				list = prev->next;
				range = 0;
				ft_printf("apres: list %s, list->next %s\n", list->name, list->next->name);
			}
			prev = list;
			list = list->next;
		}
		list = debut;
	}
	return (debut);
}
