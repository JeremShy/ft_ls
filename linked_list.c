/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 02:52:25 by jcamhi            #+#    #+#             */
/*   Updated: 2016/03/04 15:42:27 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static char	handle_type(mode_t mode)
{
	if ((mode & S_IFMT) == S_IFREG)
		return ('-');
	else if ((mode & S_IFMT) == S_IFIFO)
		return ('p');
	else if ((mode & S_IFMT) == S_IFCHR)
		return ('c');
	else if ((mode & S_IFMT) == S_IFDIR)
		return ('d');
	else if ((mode & S_IFMT) == S_IFBLK)
		return ('b');
	else if ((mode & S_IFMT) == S_IFLNK)
		return ('l');
	else if ((mode & S_IFMT) == S_IFSOCK)
		return ('s');
	else
		return ('-');
}

void	get_rights(t_file *ret, mode_t mode)
{
	ret->rights[0] = handle_type(mode);
	ret->rights[1] = (mode & S_IRUSR ? 'r' : '-');
	ret->rights[2] = (mode & S_IWUSR ? 'w' : '-');
	if (mode & S_ISUID && !(mode & S_IXUSR))
		ret->rights[3] = 'S';
	else if (mode & S_ISUID && (mode & S_IXUSR))
		ret->rights[3] = 's';
	else if (!(mode & S_ISUID) && (mode & S_IXUSR))
		ret->rights[3] = 'x';
	else
		ret->rights[3] = '-';
	ret->rights[4] = (mode & S_IRGRP ? 'r' : '-');
	ret->rights[5] = (mode & S_IWGRP ? 'w' : '-');
	if (mode & S_ISGID && !(mode & S_IXGRP))
		ret->rights[6] = 'S';
	else if (mode & S_ISGID && (mode & S_IXGRP))
		ret->rights[6] = 's';
	else if (!(mode & S_ISGID) && (mode & S_IXGRP))
		ret->rights[6] = 'x';
	else
		ret->rights[6] = '-';
	ret->rights[7] = (mode & S_IROTH ? 'r' : '-');
	ret->rights[8] = (mode & S_IWOTH ? 'w' : '-');
	if (mode & S_ISVTX && !(mode & S_IXOTH))
		ret->rights[9] = 'T';
	else if (mode & S_ISVTX && (mode & S_IXOTH))
		ret->rights[9] = 't';
	else if (!(mode & S_ISVTX) && (mode & S_IXOTH))
		ret->rights[9] = 'x';
	else
		ret->rights[9] = '-';
	ret->rights[10] = '\0';
}

t_file	*create_elem(char *path, t_file *suivant, char *name)
{
	t_file *ret;
	t_stat	structure;
	char	*c_time;
	char	*join;
	ssize_t	path_size;
	char	lnk_path[PATH_MAX];

	ret = (t_file *)malloc(sizeof(t_file));
	join = ft_strjoin(path, name);
	if (lstat(join, &structure) == -1)
	{
		join = ft_strjoinaf1(join, "/");
		print_error_fp((char*)join);
		free(join);
		return (0);
	}
	if ((structure.st_mode & S_IFMT) == S_IFLNK)
	{
		path_size = readlink(join, lnk_path, PATH_MAX - 1);
		lnk_path[path_size] = '\0';
		ret->path_to_lnk = ft_strdup(lnk_path);
	}
	else
		ret->path_to_lnk = NULL;
	free(join);
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
	ret->next = suivant;
	return (ret);
}

void	add_elem_end(char *path, t_file *list, char *name)
{
	t_file *elem;

	if (!(elem = create_elem(path, NULL, name)))
		return ;
	while (list->next != NULL)
		list = list->next;
	list->next = elem;
}

void	add_elem_end_av(char *path, t_file *list, char *name, char *av)
{
	t_file *elem;

	if (!(elem = create_elem(path, NULL, name)))
		return ;
	elem->av_name = ft_strdup(av);
	while (list->next != NULL)
		list = list->next;
	list->next = elem;
}

void	add_elem_start(char *path, t_file **list, char *name)
{
	t_file	*elem;

	elem = create_elem(path, *list, name);
	*list = elem;
}
