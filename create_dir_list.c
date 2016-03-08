/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_dir_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 19:40:20 by jcamhi            #+#    #+#             */
/*   Updated: 2016/03/08 15:43:06 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

char	*find_name(char *dup, char **av, int start)
{
	char *name;

	name = ft_strrchr(dup, (int)'/');
	if (!name)
		name = dup;
	else if (*(name + 1) == '\0' && name != av[start])
	{
		*name = '\0';
		name = ft_strrchr(dup, (int)'/');
		if (!name)
			name = dup;
		else
			name++;
	}
	else
		name++;
	return (name);
}

t_file	*create_real_list(t_file *list, t_file *list2)
{
	if (ft_strequ(list2->path, "") && ft_strequ(list2->name, ""))
	{
		free(list2->path);
		list2->path = ft_strdup("/");
	}
	if (!list)
	{
		list = create_elem(list2->path, NULL, list2->name);
		if (list)
			list->av_name = ft_strdup(list2->av_name);
	}
	else
		add_elem_end_av(list2->path, list, list2->name, list2->av_name);
	return (list);
}

t_file	*create_fake_list(char **av, int start, int ac)
{
	char	*dup;
	char	*name;
	t_file	*list2;

	list2 = NULL;
	while (start < ac)
	{
		dup = ft_strdup(av[start]);
		name = find_name(dup, av, start);
		if (!list2)
		{
			list2 = malloc(sizeof(t_file));
			ft_strncpy(list2->name, name, PATH_MAX);
			list2->path = ft_strsub(dup, 0, name - dup);
			list2->av_name = ft_strdup(av[start]);
			list2->next = NULL;
		}
		else
			add_list_with_name(list2, name, av[start], name - dup);
		start++;
		free(dup);
	}
	return (list2);
}

t_opt	init_opt(void)
{
	t_opt ret;

	ret.f = 0;
	ret.t = 0;
	ret.r = 0;
	return (ret);
}
