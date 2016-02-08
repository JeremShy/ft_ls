/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 11:22:43 by jcamhi            #+#    #+#             */
/*   Updated: 2016/02/08 17:59:30 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static long long	ft_lexic(t_file *elem1, t_file *elem2)
{
	return (ft_strcmp(elem1->name, elem2->name));
}

static long long	ft_lexic_inv(t_file *elem1, t_file *elem2)
{
	return (-1 * ft_strcmp(elem1->name, elem2->name));
}

static long long	ft_mod(t_file *elem1, t_file *elem2)
{
	if (elem2->m_time.tv_sec - elem1->m_time.tv_sec > 0)
		return (1);
	else if (elem2->m_time.tv_sec - elem1->m_time.tv_sec < 0)
		return (-1);
	else
	{
		if (elem2->m_time.tv_nsec - elem1->m_time.tv_nsec > 0)
			return (1);
		else if (elem2->m_time.tv_nsec - elem1->m_time.tv_nsec < 0)
			return (-1);
		else
			return (ft_lexic(elem1, elem2));
	}
}

static long long	ft_mod_inv(t_file *elem1, t_file *elem2)
{
	return (ft_mod(elem1, elem2) * -1);
}
t_file	*ft_sort(t_file *list, t_opt opt)
{
	static long long	(*f)(t_file *, t_file *);
	t_file		*debut;
	t_file		*tmp;
	t_file		*prev;
	int			range;

	if (!opt.t && !opt.r)
		f = ft_lexic;
	else if (opt.t && !opt.r)
		f = ft_mod;
	else if (opt.t && opt.r)
		f = ft_mod_inv;
	else if (!opt.t && opt.r)
		f = ft_lexic_inv;
	else
		ft_printf("Error while sorting");
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
