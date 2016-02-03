/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 12:12:33 by jcamhi            #+#    #+#             */
/*   Updated: 2016/02/03 22:54:49 by jcamhi           ###   ########.fr       */
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
		free(list->path);
		tmp = list->next;
		free(list);
		list = tmp;
	}
}

void	add_list_with_name(t_file *list, char *name, char *path)
{
	while (list->next)
		list = list->next;
	list->next = malloc(sizeof(t_file));
	ft_strncpy(list->next->name, name, PATH_MAX);
	list->next->path = ft_strdup(path);
	list->next->next = NULL;
}

t_file	*create_dir_list(t_opt options, int start, char **av, int ac)
{
	char	*name;
	t_file	*list2;
	t_file	*list;
	t_opt	tmp;
	int		start2;

	list2 = NULL;
	options.l = 0;
	start2 = start;
	while (start < ac)
	{
		name = ft_strrchr(av[start], (int)'/');
		if (!name)
			name = av[start];
		else if (*(name + 1) == '\0' && name != av[start])
		{
			*name = '\0';
			name = ft_strrchr(av[start], (int)'/');
			if (!name)
				name = av[start];
			else
				name++;
		}
		else
			name++;
		if (!list2)
		{
			list2 = malloc(sizeof(t_file));
			ft_strncpy(list2->name, name, PATH_MAX);
			list2->path = ft_strsub(av[start], 0, name - av[start]);
			list2->next = NULL;
		}
		else
			add_list_with_name(list2, name, av[start]);
		start++;
	}
	tmp.t = 0;
	list2 = ft_sort(list2, tmp);
	list = NULL;
	while (list2)
	{
		printf("list2->path : %s, list->name: %s\n", list2->path, list2->name);
		if (!list)
			list = create_elem(list2->path, NULL, list2->name);
		else
			add_elem_end(list2->path, list, list2->name);
		list2 = list2->next;
	}
	return (list);
}
