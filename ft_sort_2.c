/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 20:21:28 by jcamhi            #+#    #+#             */
/*   Updated: 2016/03/07 20:49:53 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

long long	ft_lexic(t_file *elem1, t_file *elem2, t_opt opt)
{
	opt.a = 0;
	return (ft_strcmp(elem1->name, elem2->name));
}

long long	ft_lexic_inv(t_file *elem1, t_file *elem2, t_opt opt)
{
	opt.a = 0;
	return (-1 * ft_strcmp(elem1->name, elem2->name));
}

long long	ft_mod(t_file *elem1, t_file *elem2, t_opt opt)
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
			return (ft_lexic(elem1, elem2, opt));
	}
}

long long	ft_mod_inv(t_file *elem1, t_file *elem2, t_opt opt)
{
	return (ft_mod(elem1, elem2, opt) * -1);
}

long long	(*init_tab(t_opt opt))(t_file *, t_file *, t_opt)
{
	long long	(*f)(t_file *, t_file *, t_opt);

	if (opt.f)
		f = ft_rights;
	else if (!opt.t && !opt.r)
	{
		f = ft_lexic;
	}
	else if (opt.t && !opt.r)
		f = ft_mod;
	else if (opt.t && opt.r)
		f = ft_mod_inv;
	else if (!opt.t && opt.r)
		f = ft_lexic_inv;
	else
		f = ft_lexic;
	return (f);
}
