/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 12:12:33 by jcamhi            #+#    #+#             */
/*   Updated: 2016/02/02 12:16:37 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_file  *set_own_grp(t_stat structure, t_file *ret)
{
	struct passwd   *pass;
	struct group    *grp;
	int             uid;

	uid = structure.st_uid;
	pass = getpwuid(uid);
	if (!pass)
		ret->owner_name = ft_itoa_base(uid, 10);
	else
		ret->owner_name = ft_strdup(pass->pw_name);
	uid = structure.st_gid;
	grp = getgrgid(uid);
	if (!grp)
		ret->group_name = ft_itoa_base(uid, 10);
	else
		ret->group_name = ft_strdup(grp->gr_name);
	return (ret);
}

void	destroy_list(t_file *list)
{
	t_file	*tmp;

	while (list)
	{
		free(list->group_name);
		free(list->owner_name);
		free(list->mounth);
		free(list->day_name);
		free(list->day_nbr);
		free(list->hour);
		free(list->min);
		free(list->sec);
		tmp = list->next;
		free(list);
		list = tmp;
	}
}
