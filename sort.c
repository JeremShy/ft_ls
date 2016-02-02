/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 11:22:43 by jcamhi            #+#    #+#             */
/*   Updated: 2016/02/02 11:31:12 by jcamhi           ###   ########.fr       */
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

	if (!opt.t)
		f = ft_lexic;
	range = 0;
	debut = list;
	while (!range)
	{
		prev = NULL;
		range = 1;
		while (list && list->next)
		{
			if (f(list, list->next) > 0)
			{
				if (prev)
					prev->next = list->next;
				if (list == debut)
					debut = list->next;
				tmp = (list->next)->next;
				(list->next)->next = list;
				list->next = tmp;
				range = 0;
			}
			prev = list;
			list = list->next;
		}
		list = debut;
	}
	return (debut);
}
