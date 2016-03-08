/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 18:33:10 by jcamhi            #+#    #+#             */
/*   Updated: 2016/03/08 16:18:17 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_file	*create_elem(char *path, t_file *suivant, char *name)
{
	t_file	*ret;
	t_stat	structure;
	char	*join;

	ret = (t_file *)malloc(sizeof(t_file));
	join = ft_strjoin(path, name);
	if (lstat(join, &structure) == -1)
	{
		join = ft_strjoinaf1(join, "/");
		print_error_fp((char*)join);
		free(join);
		free(ret);
		return (0);
	}
	ret = create_link(structure, ret, join);
	free(join);
	ret = create_2(ret, structure, name, path);
	ret->next = suivant;
	return (ret);
}

t_file	*create_2(t_file *ret, t_stat structure, char *name, char *path)
{
	char *c_time;

	ft_strncpy(ret->name, name, PATH_MAX);
	ret->name_len = ft_strlen(ret->name);
	ret->path = ft_strdup(path);
	get_rights(ret, structure.st_mode);
	if (ret->rights[0] == 'c' || ret->rights[0] == 'b')
	{
		ret->major = major(structure.st_rdev);
		ret->minor = minor(structure.st_rdev);
	}
	ret->nlinks = structure.st_nlink;
	ret = set_own_grp(structure, ret);
	ret->nbytes = structure.st_size;
	ret->m_time = structure.st_mtimespec;
	c_time = ctime(&((ret->m_time).tv_sec));
	ret->day_name = ft_strsub(c_time, 0, 3);
	ret->mounth = ft_strsub(c_time, 4, 3);
	ret->day_nbr = ft_strsub(c_time, 8, 2);
	ret->hour = ft_strsub(c_time, 11, 2);
	ret->min = ft_strsub(c_time, 14, 2);
	ret->sec = ft_strsub(c_time, 17, 2);
	ret->blocks = structure.st_blocks;
	ret->is_file = 0;
	return (ret);
}

t_file	*create_link(t_stat structure, t_file *ret, char *join)
{
	ssize_t path_size;
	char	lnk_path[PATH_MAX];

	if ((structure.st_mode & S_IFMT) == S_IFLNK)
	{
		path_size = readlink(join, lnk_path, PATH_MAX - 1);
		lnk_path[path_size] = '\0';
		ret->path_to_lnk = ft_strdup(lnk_path);
	}
	else
		ret->path_to_lnk = NULL;
	return (ret);
}
