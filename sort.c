/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 15:31:11 by jcamhi            #+#    #+#             */
/*   Updated: 2016/02/01 16:48:55 by jcamhi           ###   ########.fr       */
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
	int			range;

	if (!opt.t)
		f = ft_lexic;
	debut = list;
	range = 0;
	while (!range)
	{
		range = 1;
		while (list->next != NULL)
		{
			if (f(list, list->next) > 0)
			{
				if (range)
					debut = list->next;
				tmp = list->next;
				list->next = tmp->next;
				tmp->next = list;
				range = 0;
			}
			list = list->next;
		}
		list = debut;
	}
	return (debut);
}
