/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 02:52:25 by jcamhi            #+#    #+#             */
/*   Updated: 2016/02/01 15:47:12 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static char	handle_type(mode_t mode)
{
	if (mode & S_IFREG)
		return ('-');
	else if (mode & S_IFIFO)
		return ('p');
	else if (mode & S_IFCHR)
		return ('c');
	else if (mode & S_IFDIR)
		return ('d');
	else if (mode & S_IFBLK)
		return ('b');
	else if (mode & S_IFLNK)
		return ('l');
	else if (mode & S_IFSOCK)
		return ('s');
	else
		return ('-');
}

char	*get_rights(mode_t mode)
{
	char	*rights;

	rights = (char*)malloc(12 * sizeof(char));
	rights[0] = handle_type(mode);
	rights[1] = (mode & S_IRUSR ? 'r' : '-');
	rights[2] = (mode & S_IWUSR ? 'w' : '-');
	rights[3] = (mode & S_IXUSR ? 'x' : '-');
	rights[4] = (mode & S_IRGRP ? 'r' : '-');
	rights[5] = (mode & S_IWGRP ? 'w' : '-');
	rights[6] = (mode & S_IXGRP ? 'x' : '-');
	rights[7] = (mode & S_IROTH ? 'r' : '-');
	rights[8] = (mode & S_IWOTH ? 'w' : '-');
	rights[9] = (mode & S_IXOTH ? 'x' : '-');
	rights[10] = '\0';
	return(rights);
}

t_file	*create_elem(t_dirent dir, const char *path, t_file *suivant)
{
	t_file *ret;
	t_stat	structure;
	char	*rights;
	char	*c_time;

	ret = (t_file *)malloc(sizeof(t_file));
	if (stat(ft_strjoinaf1(ft_strjoin(path, "/"), dir.d_name), &structure) == -1)
	{
		print_error((char*)path);
		return (0);
	}
	ft_strncpy(ret->name, dir.d_name, PATH_MAX);
	ret->fileno = dir.d_ino;
	ret->name_len = ft_strlen(ret->name);
	rights = get_rights(structure.st_mode);
	ft_strncpy(ret->rights, rights, 12);
	free(rights);
	ret->nlinks = structure.st_nlink;
	ret->owner_name = getpwuid(structure.st_uid)->pw_name;
	ret->group_name = getgrgid(structure.st_gid)->gr_name;
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
	ret->next = suivant;
	return (ret);
}

void	add_elem_end(t_dirent dir, const char *path, t_file *list)
{
	t_file *elem;

	elem = create_elem(dir, path, NULL);
	while (list->next != NULL)
		list = list->next;
	list->next = elem;
}

void	add_elem_start(t_dirent dir, const char *path, t_file **list)
{
	t_file	*elem;

	elem = create_elem(dir, path, *list);
	*list = elem;
}
